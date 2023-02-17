#if !defined(__E81A04B6_16B7_4A3C_9B7D_627AD8478765__)
#define __E81A04B6_16B7_4A3C_9B7D_627AD8478765__

namespace local {

 class CmdLine {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  CmdLine();
  ~CmdLine();
 private:
  void Init();
  void UnInit();
 public:
  const bool& ProxyEnable() const;
  const std::string ProxyAccount() const;
  const std::string ProxyAddress() const;
  const std::string ProxyPassword() const;
 private:
  bool m_EnableProxy = false;
  std::string m_ProxyAccount;
  std::string m_ProxyPassword;
  std::string m_ProxyAddress;
 };

}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 17 Feb 2023 02:31:19 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__E81A04B6_16B7_4A3C_9B7D_627AD8478765__
