#if !defined(__794468B0_0ABF_4792_8D17_7C8C2251F73E__)
#define __794468B0_0ABF_4792_8D17_7C8C2251F73E__

namespace local {

 class Main final {
 protected:
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Main();
  virtual ~Main();
  void Release() const;
 private:
  void Init();
  void UnInit();
 };

 extern Main* __gpMain;
}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 24 Feb 2023 15:27:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__794468B0_0ABF_4792_8D17_7C8C2251F73E__
