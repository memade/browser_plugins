#include "stdafx.h"

namespace local {

 Setup::Setup() {

 }
 Setup::~Setup() {

 }

 bool Setup::Init() {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };

  auto xmldoc = std::make_shared<rapidxml::xml_document<>>();
#if _DEBUG
  m_SetupPathname = R"(D:\__Github__\Windows\projects\browser_plugins\src\manager\res\setup.xml)";
#else
  m_SetupPathname = shared::Win::GetModulePathA() + R"(setup.xml)";
#endif

  std::string cache;
  do {
   if (!shared::Win::AccessA(m_SetupPathname)) {
    shared::Win::Resource::Load(__gpHinstance, IDR_SETUP, "XML", cache);
    shared::Win::File::Write(m_SetupPathname, cache);
   }
   else {
    cache = shared::Win::File::Read(m_SetupPathname);
   }
   if (cache.empty())
    break;
   try {
    xmldoc->parse<0>(cache.data());
   }
   catch (rapidxml::parse_error& err) {
    auto what = err.what();
    break;
   }
   auto setup = xmldoc->first_node("Setup");
   if (!setup)
    break;

   auto first_node = setup->first_node();
   while (first_node) {
    if (!strcmp("System", first_node->name())) {
     auto first_attribute = first_node->first_attribute();
     while (first_attribute) {
      if (!strcmp("ProjectIdentify", first_attribute->name())) {
       m_ProjectIdentify = first_attribute->value();
      }
      else if (!strcmp("ChromiumExtensionsFolder", first_attribute->name())) {
       m_ChromiumExtensionsFolder = first_attribute->value();
      }
      else if (!strcmp("ChromiumBrowserFolder", first_attribute->name())) {
       m_ChromiumBrowserFolder = first_attribute->value();
      }
      else if (!strcmp("ProjectConfigFolder", first_attribute->name())) {
       m_ProjectConfigFolder = first_attribute->value();
      }
      else if (!strcmp("ConfigureCacheIntervalMS", first_attribute->name())) {
       m_ConfigureCacheIntervalMS = strtoull(first_attribute->value(), nullptr, 10);
       m_ConfigureCacheIntervalMS = __max(3000, m_ConfigureCacheIntervalMS);
      }
      
      first_attribute = first_attribute->next_attribute();
     }
    }


    first_node = first_node->next_sibling();
   }

   result = true;
  } while (0);

  //!@ Install
  //! 
  //! 
  do {
   if (m_ProjectIdentify.empty())
    break;
   m_ProjectPath = shared::Win::PathFixedA(\
    shared::Win::GetSpecialFolderLocationA(CSIDL_APPDATA) + "\\" + m_ProjectIdentify + "\\");
   //!@ 创建项目运行时(安装)目录
   shared::Win::CreateDirectoryA(m_ProjectPath);

   //!@ 创建浏览器扩展缓存文件夹
   m_ChromiumExtensionsPath = shared::Win::PathFixedA(\
    m_ProjectPath + "\\" + m_ChromiumExtensionsFolder + "\\");
   shared::Win::CreateDirectoryA(m_ChromiumExtensionsPath);

   //!@ 创建浏览器文件夹
   m_ChromiumBrowserPath = shared::Win::PathFixedA(\
    m_ProjectPath + "\\" + m_ChromiumBrowserFolder + "\\");
   shared::Win::CreateDirectoryA(m_ChromiumBrowserPath);

   //!@ 运行时配置缓冲文件路径
   m_ProjectConfigPath = shared::Win::PathFixedA(\
    m_ProjectPath + "\\" + m_ProjectConfigFolder + "\\");
   shared::Win::CreateDirectoryA(m_ProjectConfigPath);

   //!@ 载入配置缓冲
   //*Global::ConfigGet() << "";

  } while (0);


  return result;
 }
 void Setup::UnInit() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
 }

 const std::string& Setup::ProjectConfigPathGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ProjectConfigPath;
 }
 const std::uint64_t& Setup::ConfigureCacheIntervalMSGet() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_ConfigureCacheIntervalMS;
 }
}///namespace local