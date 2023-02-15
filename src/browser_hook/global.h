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
  static ChromiumPluginUI* PluginUIGet();
 private:
  void Init();
  void UnInit();
 private:
  std::atomic_bool m_Ready = false;
  ChromiumPlugin* m_pChromiumPlugin = nullptr;
  ChromiumPluginUI* m_pChromiumPluginUI = nullptr;
 };

 extern Global* GlobalGet();
 extern HHOOK __gpHhook;
 extern HINSTANCE __gpHinstance;
}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 09 Feb 2023 07:36:10 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__5377695D_E8D7_468C_AD14_5D0EF50ADD17__


