#if !defined(__8AF6721F_3050_4B1E_A90A_5EEB81D01643__)
#define __8AF6721F_3050_4B1E_A90A_5EEB81D01643__

namespace local {
 class IApp : public wxApp {
 public:
  IApp();
  virtual ~IApp();
 private:
  void OnCreateFrame(wxThreadEvent& event);
  void OnDestory(wxThreadEvent& event);
 public:
  bool OnInit() override;
  int OnExit() override;
  wxFrame* FrameGet() const;
  void RegisterAppInitEventCb(const shared::wx::tfAppInitEventCallback&);
  void RegisterAppCloseEventNotifyCb(const shared::wx::tfAppCloseEventNotifyCallback&);
  void RegisterAppCreateFrameEventCb(const shared::wx::tfAppCreateFrameEventCallback&);
 protected:
  std::vector<std::thread> m_Threads;
  wxFrame* m_pFrame = nullptr;
  shared::wx::tfAppInitEventCallback m_AppInitEventCb = nullptr;
  shared::wx::tfAppCloseEventNotifyCallback m_AppCloseEventNotifyCb = nullptr;
  shared::wx::tfAppCreateFrameEventCallback m_AppCreateFrameEventCb = nullptr;
 };
}

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 10 Feb 2023 03:50:27 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__8AF6721F_3050_4B1E_A90A_5EEB81D01643__