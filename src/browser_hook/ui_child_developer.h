#if !defined(__C0C17683_B26D_4A03_9AC0_8E6D2550A392__)
#define __C0C17683_B26D_4A03_9AC0_8E6D2550A392__

namespace local {
 class IChildConfigureDeveloper : public wxMDIChildFrame {
 public:
  IChildConfigureDeveloper(wxMDIParentFrame* parent,
   const wxWindowID& id = wxID_ANY,
   const wxString& title = _("开发者配置"),
   const wxPoint& pos = wxDefaultPosition,
   const wxSize& size = wxDefaultSize);
  virtual ~IChildConfigureDeveloper();
 private:
  void OnPaneClose(wxAuiManagerEvent&);
  void OnActivate(wxActivateEvent&);
  void OnSize(wxSizeEvent&);
  void OnMove(wxMoveEvent&);
  void OnCloseWindow(wxCloseEvent&);
  void OnUpdateUI(wxUpdateUIEvent&);
 private:
  wxAuiManager m_AuiManager;
  wxDECLARE_EVENT_TABLE();
 };
}

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 12 Feb 2023 03:28:26 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__C0C17683_B26D_4A03_9AC0_8E6D2550A392__

