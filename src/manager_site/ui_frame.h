#if !defined(__FBB21A96_6B3E_4803_961B_C1AD168292BA__)
#define __FBB21A96_6B3E_4803_961B_C1AD168292BA__

namespace local {

 class UICefFrame : public ICefFrame {
 public:
  UICefFrame();
  virtual ~UICefFrame();
 protected:
  ui::Control* CreateControl(const std::wstring& pstrClass) override final;
  void InitWindow() override final;
  LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
 private:
  bool OnClicked(ui::EventArgs* msg);
  bool OnNavigate(ui::EventArgs* msg);
  void OnLoadBegin();
  void OnLoadEnd(int httpStatusCode);

  void OnLoadBeginLocal();
  void OnLoadEndLocal(int httpStatusCode);

  bool OnBtnc2jtest(ui::EventArgs*);
 private:
  nim_comp::CefControlBase* m_pCefMain = nullptr;
  nim_comp::CefControlBase* m_pCefMainLocal = nullptr;
 };














 class UIFrame : public IFrame {
 public:
  UIFrame();
  ~UIFrame();
 protected:
  void Release() const override final;
  void InitWindow() override final;
  bool OnTreeViewSelected(ui::EventArgs*);
  bool OnBtnSystemClose(ui::EventArgs*);
  bool OnBtnBrowserConfigSave(ui::EventArgs*);
  bool OnBtnBrowserConfigStart(ui::EventArgs*);
  bool OnCheckProxySelected(ui::EventArgs*);
  bool OnCheckProxyUnSelected(ui::EventArgs*);
  bool OnBtnBrowserConfigCreate(ui::EventArgs*);
  bool OnBtnBrowserConfigRemove(ui::EventArgs*);
  bool OnListboxUserBrowserConfigSelected(ui::EventArgs*);

  LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
  LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
 private:
  ui::Label* m_pLabelSystemTitle = nullptr;
  ui::TreeView* m_pTreeviewMain = nullptr;
  ui::TabBox* m_pTabboxMain = nullptr;
  ui::Button* m_pBtnSystemClose = nullptr;
  ui::Button* m_pBtnSystemMin = nullptr;
  ui::Button* m_pBtnSystemMax = nullptr;
  ui::Button* m_pBtnBrowserConfigCreate = nullptr;
  ui::Button* m_pBtnBrowserConfigRemove = nullptr;
  ui::Button* m_pBtnBrowserConfigSave = nullptr;
  ui::Button* m_pBtnBrowserStartProgram = nullptr;
  UIUserBrowserConfigListbox* m_pListboxUserBrowserConfig = nullptr;
  UIUserBrowserConfigPage* m_pUserBrowserConfigPage = nullptr;
  const std::wstring kClassName = L"Main";
 };


}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 18 Feb 2023 17:37:08 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__FBB21A96_6B3E_4803_961B_C1AD168292BA__