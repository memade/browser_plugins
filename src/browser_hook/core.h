#if !defined(__7B4C22FB_0978_49CE_95AF_76A0AEEF317A__)
#define __7B4C22FB_0978_49CE_95AF_76A0AEEF317A__

namespace local {

 class Core final {
 public:
  Core();
  ~Core();
 private:
  void Init();
  void UnInit();
 public:
  bool Open();
  void Close();
 private:
  std::atomic_bool m_IsOpen = false;
 };

}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 30 Jan 2023 04:20:09 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__7B4C22FB_0978_49CE_95AF_76A0AEEF317A__

