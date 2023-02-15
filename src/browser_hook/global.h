#if !defined(__5377695D_E8D7_468C_AD14_5D0EF50ADD17__)
#define __5377695D_E8D7_468C_AD14_5D0EF50ADD17__

namespace local {

 class Global final {
 public:
  Global();
  ~Global();
 public:
  static bool Ready();
  static void GoogleApiKeyInit();
  static ChromiumPlugin* PluginGet();
#if ENABLE_UI
  static ChromiumPluginUI* PluginUIGet();
#endif
 private:
  void Init();
  void UnInit();
 private:
  std::atomic_bool m_Ready = false;
  ChromiumPlugin* m_pChromiumPlugin = nullptr;
#if ENABLE_UI
  ChromiumPluginUI* m_pChromiumPluginUI = nullptr;
#endif
 public:
  tfCommandLineNode m_CmdLineParseMap;
 };

 extern Global* __gpGlobal;
 extern HHOOK __gpHhook;
 extern HINSTANCE __gpHinstance;
}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 09 Feb 2023 07:36:10 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__5377695D_E8D7_468C_AD14_5D0EF50ADD17__


