#if !defined(__1CBB39D8_AF8E_4D3C_82EA_77531CC65945__)
#define __1CBB39D8_AF8E_4D3C_82EA_77531CC65945__

namespace local {

 enum class EnBrowserProcessType : unsigned long long {
  EN_PROCESS_TYPE_UNKNOWN = 0x0000,
  EN_PROCESS_TYPE_MAIN = 0x1000,
  EN_PROCESS_TYPE_GPU = 0x2000,
  EN_PROCESS_TYPE_RENDERER = 0x3000,
  EN_PROCESS_TYPE_UTILITY = 0x4000,
  EN_PROCESS_TYPE_CRASHPAD = 0x5000,
 };

 typedef struct tagBrowserConfig final {
 public:
  std::vector<std::string> UserAgents;
  std::vector<std::string> Platforms;
  std::vector<std::uint16_t> HardwareConcurencys;

 }BrowserConfig;
 class Config final {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Config();
  ~Config();
 public:
  void Init();
  void UnInit();
 public:
  void Release() const;
 private:
  bool m_MainSwitch = false;
  bool m_Hookup_GetNativeSystemInfo = false;
  std::string m_ConfigPathname;
 };

}
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 12 Feb 2023 05:15:21 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__1CBB39D8_AF8E_4D3C_82EA_77531CC65945__
