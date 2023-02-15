#if !defined(__977065DC_42FB_448F_A8D9_AF31F24AFE54__)
#define __977065DC_42FB_448F_A8D9_AF31F24AFE54__

namespace local {

 class ChromiumPluginUI : public shared::ui::UIFrame {
 public:
  ChromiumPluginUI();
  virtual ~ChromiumPluginUI();
 public:
  bool Start();
  void Stop();
  bool InstallKeyHook() const;
  void UninstallKeyHook() const;
  void ShowControl() const;
 private:
  void Init();
  void UnInit();
 protected:
  void InitWindow() override final;
  void Notify(TNotifyUI& msg) override final;
  void OnFinalMessage(HWND hWnd) override final { delete this; }
  CControlUI* CreateControl(LPCTSTR pstrClassName) override final;
  LPCTSTR GetWindowClassName() const override final { return _TEXT("main"); }
  LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
 private:
  void MainProcess();
  bool NotifyMainCreateEvent();
  HANDLE m_hUIMainT = nullptr;
  HANDLE m_hUIMainCreateEvent = nullptr;
  CTreeViewUI* m_pUITreeViewMain = nullptr;
  CTabLayoutUI* m_pUITablayoutMain = nullptr;
 protected:
  std::atomic_bool m_IsOpenUI = false;
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 };

}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 14 Feb 2023 04:02:51 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__977065DC_42FB_448F_A8D9_AF31F24AFE54__



