#if !defined(__8AE6EF8C_A146_44E8_A840_05B743D90B14__)
#define __8AE6EF8C_A146_44E8_A840_05B743D90B14__

namespace local {

 class Setup final {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Setup();
  ~Setup();
 public:
  bool Init();
  void UnInit();
 public:
  const std::string& ProjectConfigPathGet() const;
  const std::uint64_t& ConfigureCacheIntervalMSGet() const;
 private:
  std::string m_SetupPathname;
  std::string m_ProjectPath;
  std::string m_ProjectIdentify;
  std::string m_ChromiumExtensionsFolder;
  std::string m_ChromiumExtensionsPath;
  std::string m_ChromiumBrowserFolder;
  std::string m_ChromiumBrowserPath;
  std::string m_ProjectConfigFolder;
  std::string m_ProjectConfigPath;
  std::uint64_t m_ConfigureCacheIntervalMS = 3000;
 };



}

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 19 Feb 2023 08:42:41 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__8AE6EF8C_A146_44E8_A840_05B743D90B14__