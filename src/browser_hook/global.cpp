#include "stdafx.h"

namespace local {
 static Global __gsGlobal;
 Global* GlobalGet() { return &__gsGlobal; }

 Global::Global() {
  Init();
 }

 Global::~Global() {
  UnInit();
 }

 void Global::Init() {
  const std::string current_process_path = shared::Win::GetModulePathA(__gpHinstance);

  GoogleApiKeyInit();
  m_pChromiumPlugin = new ChromiumPlugin();
  if (m_pChromiumPlugin->BrowserProcessType() == EnBrowserProcessType::EN_PROCESS_TYPE_MAIN) {
   m_pChromiumPluginUI = new ChromiumPluginUI();
   __gpSpdlog = shared::ISpdlog::CreateInterface("main", current_process_path + R"(\logs\)");
  }

  m_Ready.store(true);
  do {
   //   auto setup = shared::Win::File::Read(
   //#if _DEBUG
   //    R"(D:\__Github__\Windows\projects\browser_plugins\src\browser_hook\res\setup.xml)"
   //#else
   //    current_process_path + R"(setup.xml)"
   //#endif
   //   );
      //m_pConfig = new Config();
      //if (!(*m_pConfig << setup))
      // break;
      //std::string gbk_config_buffer;
      //*m_pConfig >> gbk_config_buffer;
      //!@ 只有主进程才创建日志
      //LPSTR input_args = ::GetCommandLineA();
      //if (!input_args || (::StrStrIA(input_args, "--type=") == nullptr)) {
      // __gpSpdlog = shared::ISpdlog::CreateInterface("main", current_process_path + R"(\logs\)");
      //}

  } while (0);
 }

 void Global::UnInit() {
  shared::ISpdlog::DestoryInterface(__gpSpdlog);
  SK_DELETE_PTR(m_pChromiumPlugin);
  SK_DELETE_PTR(m_pChromiumPluginUI);
  m_Ready.store(false);
 }
 bool Global::Ready() {
  return __gsGlobal.m_Ready.load();
 }

 void Global::GoogleApiKeyInit() {
  if (!::getenv("GOOGLE_API_KEY"))
   ::_putenv_s("GOOGLE_API_KEY", "no");
  if (!::getenv("GOOGLE_DEFAULT_CLIENT_ID"))
   ::_putenv_s("GOOGLE_DEFAULT_CLIENT_ID", "no");
  if (!::getenv("GOOGLE_DEFAULT_CLIENT_SECRET"))
   ::_putenv_s("GOOGLE_DEFAULT_CLIENT_SECRET", "no");
 }

 ChromiumPlugin* Global::PluginGet() {
  return __gsGlobal.m_pChromiumPlugin;
 }
 ChromiumPluginUI* Global::PluginUIGet() {
  return __gsGlobal.m_pChromiumPluginUI;
 }


 HHOOK __gpHhook = nullptr;
 HINSTANCE __gpHinstance = nullptr;

}///namespace local