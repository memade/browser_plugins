#if !defined(__CAF31354_C62D_433E_BB9A_A7BCCF1D1AED__)
#define __CAF31354_C62D_433E_BB9A_A7BCCF1D1AED__

namespace local {

 class IMDIParentFrame : public wxMDIParentFrame {
 public:
  IMDIParentFrame(wxWindow* parent = nullptr,
   const wxWindowID& id = wxID_ANY,
   const wxString& title = L"",
   const wxPoint& pos = wxDefaultPosition,
   const wxSize& size = wxSize(1024, 768),
   long style = /*wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER*/
   wxSYSTEM_MENU | \
   wxMINIMIZE_BOX | \
   /*wxRESIZE_BORDER | \
   wxMINIMIZE_BOX | \
   wxMAXIMIZE_BOX | \*/
   wxCLOSE_BOX | \
   wxCAPTION | \
   wxCLIP_CHILDREN);
  virtual ~IMDIParentFrame();
 protected:
  void OnSize(wxSizeEvent&);
  void OnClose(wxCloseEvent&);
  void OnAbout(wxCommandEvent&);
  WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) wxOVERRIDE;
 private:
  IChildConfigure* m_pChildConfig = nullptr;
  wxToolBar* m_pToolbarMain = nullptr;
  wxMenuBar* m_pMenuMain = nullptr;
  wxStatusBar* m_pStatusbarMain = nullptr;
  wxDECLARE_EVENT_TABLE();
 };

}

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 10 Feb 2023 03:52:09 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__CAF31354_C62D_433E_BB9A_A7BCCF1D1AED__

