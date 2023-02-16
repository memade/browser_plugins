#include "stdafx.h"

namespace local {

 Global::Global() {
  Init();
 }

 Global::~Global() {
  UnInit();
 }

 void Global::Init() {
  
  auto pCmdline = ::GetCommandLineA();
  std::string cmdline = pCmdline ? pCmdline : "";
  do {
   auto found = cmdline.find("--memade=");
   if (found == std::string::npos)
    break;
   std::string value, decode;
   std::vector<std::string> parses;
   shared::Win::File::ParseA(cmdline.data() + found, '=', parses);
   if (parses.size() < 2)
    break;
   value = parses[1];
   if (value.empty())
    break;
   decode = shared::Encryption::base64::base64_decode(value);
   shared::Win::ParseCommandLineParameters(decode, m_CmdLineParseMap);
  } while (0);
  
  const std::string current_process_path = shared::Win::GetModulePathA(__gpHinstance);

  const std::string current_process_id = std::to_string(::GetCurrentProcessId());

  GoogleApiKeyInit();
  m_pChromiumPlugin = new ChromiumPlugin();
  m_pChromiumPlugin->Start();
  if (m_pChromiumPlugin->BrowserProcessType() == EnBrowserProcessType::EN_PROCESS_TYPE_MAIN) {
#if ENABLE_UI
   m_pChromiumPluginUI = new ChromiumPluginUI();
#endif
   __gpSpdlog = shared::ISpdlog::CreateInterface("main", current_process_path + R"(\logs\)");
  }
  else {
   __gpSpdlog = shared::ISpdlog::CreateInterface(current_process_id, current_process_path + R"(\logs\)" + current_process_id);
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
  if (m_pChromiumPlugin)
   m_pChromiumPlugin->Stop();
  SK_DELETE_PTR(m_pChromiumPlugin);
#if ENABLE_UI
  SK_DELETE_PTR(m_pChromiumPluginUI);
#endif
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

 ChromiumPlugin* Global::PluginGet() {
  if (__gpGlobal)
   return __gpGlobal->m_pChromiumPlugin;
  return nullptr;
 }
#if ENABLE_UI
 ChromiumPluginUI* Global::PluginUIGet() {
  return __gsGlobal.m_pChromiumPluginUI;
 }
#endif


 HHOOK __gpHhook = nullptr;
 HINSTANCE __gpHinstance = nullptr;
 Global* __gpGlobal = nullptr;
}///namespace local