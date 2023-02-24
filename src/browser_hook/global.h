#if !defined(__5377695D_E8D7_468C_AD14_5D0EF50ADD17__)
#define __5377695D_E8D7_468C_AD14_5D0EF50ADD17__

namespace local {
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
 class PluginData final {
 public:
  bool operator<<(const std::string&);
 public:
  std::string user_agent;
  size_t screen_resolution = 10;
  size_t available_screen_size = 10;
  size_t hardware_concurency = 1;
  std::string platform;
  std::string webgl_version;
  std::string webgl_unmasked_vendor;
  std::string webgl_unmasked_renderer;
 };

 class Global final {
 public:
  Global();
  ~Global();
 public:
  static bool Ready();
  static Config* ConfigGet();
  static void GoogleApiKeyInit();
  static ChromiumPlugin* PluginGet();
  static std::string CurrentCmdlineCacheGet();
  static EnBrowserProcessType BrowserProcessTypeGet();
 public:
  const PluginData& PluginDataGet() const;
#if ENABLE_UI
  static ChromiumPluginUI* PluginUIGet();
#endif
 private:
  void Init();
  void UnInit();
 private:
  std::atomic_bool m_Ready = false;
  Config* m_pConfig = nullptr;
  ChromiumPlugin* m_pChromiumPlugin = nullptr;
  Extensions* m_pChromiumExtensions = nullptr;
  PluginData m_PluginData;
#if ENABLE_UI
  ChromiumPluginUI* m_pChromiumPluginUI = nullptr;
#endif
  const std::string m_CurrentCmdlineCache;
  EnBrowserProcessType m_BrowserProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_UNKNOWN;
 private:
  void BrowserProcessTypeInit();
  void PluginDataInit();
 };

 extern CmdLine* __gpCmdline;
 extern Global* __gpGlobal;
 extern HHOOK __gpHhook;
 extern HINSTANCE __gpHinstance;
}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 09 Feb 2023 07:36:10 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__5377695D_E8D7_468C_AD14_5D0EF50ADD17__


