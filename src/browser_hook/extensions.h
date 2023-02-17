#if !defined(__C15F88C0_8312_420A_86D9_9510B3B29689__)
#define __C15F88C0_8312_420A_86D9_9510B3B29689__

namespace local {

 class Extensions {
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Extensions();
  ~Extensions();
 private:
  void Init();
  void UnInit();
 public:
  
 };

}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 17 Feb 2023 01:52:39 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__C15F88C0_8312_420A_86D9_9510B3B29689__
