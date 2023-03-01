#if !defined(__352272B8_ECCA_4248_AC53_211033794B16__)
#define __352272B8_ECCA_4248_AC53_211033794B16__

namespace local {
 class App : public wxApp {
 public:
  App();
  virtual ~App();
 protected:
  bool OnInit() override;
  int OnExit() override;
  wxFrame* FrameGet() const;
 private:
  wxFrame* m_pFrame = nullptr;
 };
}

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 09 Feb 2023 05:23:19 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__352272B8_ECCA_4248_AC53_211033794B16__

