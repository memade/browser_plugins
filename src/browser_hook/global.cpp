#include "stdafx.h"

namespace local {

 Global::Global() :
  m_CurrentCmdlineCache(::GetCommandLineA() ? ::GetCommandLineA() : "") {
  Init();
 }

 Global::~Global() {
  UnInit();
 }

 void Global::Init() {
  BrowserProcessTypeInit();
  PluginDataInit();
  const std::string current_process_path = shared::Win::GetModulePathA(__gpHinstance);
  const std::string current_process_id = std::to_string(::GetCurrentProcessId());
  if (m_BrowserProcessType == EnBrowserProcessType::EN_PROCESS_TYPE_MAIN) {
   __gpSpdlog = shared::ISpdlog::CreateInterface("main", current_process_path + R"(\logs\)");
  }
  m_pConfig = new Config();

  GoogleApiKeyInit();
  m_pChromiumPlugin = new ChromiumPlugin();
  m_pChromiumPlugin->Start();

  m_pChromiumExtensions = new Extensions();
  m_Ready.store(true);
 }

 void Global::UnInit() {
  SK_DELETE_PTR(m_pChromiumExtensions);
  if (m_pChromiumPlugin)
   m_pChromiumPlugin->Stop();
  SK_DELETE_PTR(m_pChromiumPlugin);
#if ENABLE_UI
  SK_DELETE_PTR(m_pChromiumPluginUI);
#endif
  SK_DELETE_PTR(m_pConfig);
  shared::ISpdlog::DestoryInterface();
  m_Ready.store(false);
 }
 bool Global::Ready() {
  if (!__gpGlobal)
   return false;
  return __gpGlobal->m_Ready.load();
 }

 void Global::GoogleApiKeyInit() {
  if (!::getenv("GOOGLE_API_KEY"))
   ::_putenv_s("GOOGLE_API_KEY", "no");
  if (!::getenv("GOOGLE_DEFAULT_CLIENT_ID"))
   ::_putenv_s("GOOGLE_DEFAULT_CLIENT_ID", "no");
  if (!::getenv("GOOGLE_DEFAULT_CLIENT_SECRET"))
   ::_putenv_s("GOOGLE_DEFAULT_CLIENT_SECRET", "no");
 }
 const PluginData& Global::PluginDataGet() const {
  return m_PluginData;
 }
 Config* Global::ConfigGet() {
  if (__gpGlobal)
   return __gpGlobal->m_pConfig;
  return nullptr;
 }
 std::string Global::CurrentCmdlineCacheGet() {
  std::string result;
  if (__gpGlobal)
   result = __gpGlobal->m_CurrentCmdlineCache;
  return result;
 }
 ChromiumPlugin* Global::PluginGet() {
  if (__gpGlobal)
   return __gpGlobal->m_pChromiumPlugin;
  return nullptr;
 }
 EnBrowserProcessType Global::BrowserProcessTypeGet() {
  EnBrowserProcessType result = EnBrowserProcessType::EN_PROCESS_TYPE_UNKNOWN;
  if (__gpGlobal)
   result = __gpGlobal->m_BrowserProcessType;
  return result;
 }
 void Global::PluginDataInit() {
  do {
   auto found = m_CurrentCmdlineCache.find("--load-plugin=");
   if (found == std::string::npos)
    break;
   std::string plugin_config_pathname;
   for (size_t i = found + strlen("--load-plugin="); i < m_CurrentCmdlineCache.size(); ++i) {
    if (m_CurrentCmdlineCache[i] == ' ' || m_CurrentCmdlineCache[i] == '\r' || m_CurrentCmdlineCache[i] == '\n')
     break;
    plugin_config_pathname.push_back(m_CurrentCmdlineCache[i]);
   }
   if (!shared::Win::AccessA(plugin_config_pathname))
    break;
   m_PluginData << shared::Win::File::Read(plugin_config_pathname);
  } while (0);
 }
 void Global::BrowserProcessTypeInit() {
  m_BrowserProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_UNKNOWN;
  do {
   if (m_CurrentCmdlineCache.empty()) {
    m_BrowserProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_MAIN;
    break;
   }
   if (m_CurrentCmdlineCache.find("--type=") == std::string::npos) {
    m_BrowserProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_MAIN;
    break;
   }
   if (m_CurrentCmdlineCache.find("--type=gpu-process ") != std::string::npos) {
    m_BrowserProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_GPU;
    break;
   }
   if (m_CurrentCmdlineCache.find("--type=renderer ") != std::string::npos) {
    m_BrowserProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_RENDERER;
    break;
   }
   if (m_CurrentCmdlineCache.find("--type=utility ") != std::string::npos) {
    m_BrowserProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_UTILITY;
    break;
   }
   if (m_CurrentCmdlineCache.find("--type=crashpad-handler ") != std::string::npos) {
    m_BrowserProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_CRASHPAD;
    break;
   }
  } while (0);
 }
#if ENABLE_UI
 ChromiumPluginUI* Global::PluginUIGet() {
  return __gsGlobal.m_pChromiumPluginUI;
  }
#endif

 /*
{
    "identify":1677128424027456,
    "name":"开发测试配置",
    "comment":"配置说明信息",
    "jumpurl":"https://cn.bing.com/",
    "proxy_address":"http://proxy.ipidea.io:2333/",
    "proxy_account":"liyz888-zone-custom-region-us-session-86977717-sessTime-60",
    "proxy_password":"c646674de314d7f2",
    "proxy_enable":true,
    "user_agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36",
    "screen_resolution":10,
    "available_screen_size":20,
    "hardware_concurency":32,
    "platform":"Win16",
    "webgl_unmasked_vendor":"ANGLE (NVIDIA, NVIDIA Quadro 2000M Direct3D11 vs_5_0 ps_5_0)",
    "webgl_unmasked_renderer":"Google Inc. (NVIDIA)",
    "webgl_version":"WebGL 1.0 (OpenGL ES 2.0 Chromium)"
}
 */
 bool PluginData::operator<<(const std::string& input_json_data) {
  bool result = false;
  do {
   if (input_json_data.empty())
    break;
   rapidjson::Document doc;
   if (doc.Parse(input_json_data.data(), input_json_data.size()).HasParseError())
    break;

   if (!doc.IsObject())
    break;
   if (doc.ObjectEmpty())
    break;

   if (doc.HasMember(SK_VNAME(screen_resolution)) && doc[SK_VNAME(screen_resolution)].IsNumber())
    screen_resolution = doc[SK_VNAME(screen_resolution)].GetUint64();
   if (doc.HasMember(SK_VNAME(available_screen_size)) && doc[SK_VNAME(available_screen_size)].IsNumber())
    available_screen_size = doc[SK_VNAME(available_screen_size)].GetUint64();
   if (doc.HasMember(SK_VNAME(hardware_concurency)) && doc[SK_VNAME(hardware_concurency)].IsNumber())
    hardware_concurency = doc[SK_VNAME(hardware_concurency)].GetUint64();

   if (doc.HasMember(SK_VNAME(user_agent)) && doc[SK_VNAME(user_agent)].IsString())
    user_agent = doc[SK_VNAME(user_agent)].GetString();
   if (doc.HasMember(SK_VNAME(platform)) && doc[SK_VNAME(platform)].IsString())
    platform = doc[SK_VNAME(platform)].GetString();
   if (doc.HasMember(SK_VNAME(webgl_unmasked_vendor)) && doc[SK_VNAME(webgl_unmasked_vendor)].IsString())
    webgl_unmasked_vendor = doc[SK_VNAME(webgl_unmasked_vendor)].GetString();
   if (doc.HasMember(SK_VNAME(webgl_unmasked_renderer)) && doc[SK_VNAME(webgl_unmasked_renderer)].IsString())
    webgl_unmasked_renderer = doc[SK_VNAME(webgl_unmasked_renderer)].GetString();
   if (doc.HasMember(SK_VNAME(webgl_version)) && doc[SK_VNAME(webgl_version)].IsString())
    webgl_version = doc[SK_VNAME(webgl_version)].GetString();

   result = true;
  } while (0);
  return result;
 }


 CmdLine* __gpCmdline = nullptr;
 HHOOK __gpHhook = nullptr;
 HINSTANCE __gpHinstance = nullptr;
 Global* __gpGlobal = nullptr;
 }///namespace local