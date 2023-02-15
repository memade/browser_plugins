#if !defined(__500D02AD_125B_4980_81AC_1611C0F58CB5__)
#define __500D02AD_125B_4980_81AC_1611C0F58CB5__


namespace local {
 class TreeCtrlMain : public wxTreeCtrl {
 public:
  TreeCtrlMain(wxWindow* parent, 
   wxWindowID id = wxID_ANY,
   const wxPoint& pos = wxDefaultPosition,
   const wxSize& size = wxDefaultSize,
   long style = /*wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT*/wxTR_DEFAULT_STYLE /*| wxNO_BORDER*/,
   const wxValidator& validator = wxDefaultValidator,
   const wxString& name = wxASCII_STR(wxTreeCtrlNameStr));
  virtual ~TreeCtrlMain();

 private:
  //wxDECLARE_DYNAMIC_CLASS(TreeCtrlMain);
  wxDECLARE_EVENT_TABLE();
 };

}


/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 12 Feb 2023 03:30:08 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__500D02AD_125B_4980_81AC_1611C0F58CB5__
