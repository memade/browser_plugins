#if !defined(__D3D87FC8_598A_4F79_B230_10ACA22809EE__)
#define __D3D87FC8_598A_4F79_B230_10ACA22809EE__


namespace local {
 class IChildConfigure : public wxMDIChildFrame {
 public:
  IChildConfigure(wxMDIParentFrame* parent,
   wxWindowID id = wxID_ANY,
   const wxString& title = "",
   const wxPoint& pos = wxDefaultPosition,
   const wxSize& size = wxDefaultSize,
   long style = /*wxDEFAULT_FRAME_STYLE*//*wxCAPTION | wxCLIP_CHILDREN*/wxNO_BORDER,
   const wxString& name = wxASCII_STR(wxFrameNameStr));
  virtual ~IChildConfigure();
 private:
  void OnPaneClose(wxAuiManagerEvent&);
  void OnActivate(wxActivateEvent&);
  void OnSize(wxSizeEvent&);
  void OnMove(wxMoveEvent&);
  void OnCloseWindow(wxCloseEvent&);
  void OnUpdateUI(wxUpdateUIEvent&);
 private:
  TreeCtrlMain* m_pTreeCtrlMain = nullptr;
 private:
  wxAuiManager m_AuiManager;
  wxDECLARE_EVENT_TABLE();
 };
}


/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 10 Feb 2023 06:46:31 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__D3D87FC8_598A_4F79_B230_10ACA22809EE__
