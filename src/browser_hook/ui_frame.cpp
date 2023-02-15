#include "stdafx.h"

namespace local {

 wxBEGIN_EVENT_TABLE(IMDIParentFrame, wxMDIParentFrame)
  EVT_SIZE(IMDIParentFrame::OnSize)
  EVT_CLOSE(IMDIParentFrame::OnClose)
  EVT_MENU(wxID_ABOUT, IMDIParentFrame::OnAbout)
  wxEND_EVENT_TABLE();

 IMDIParentFrame::IMDIParentFrame(
  wxWindow* parent,
  const wxWindowID& id,
  const wxString& title,
  const wxPoint& pos,
  const wxSize& size,
  long style) :
  wxMDIParentFrame(parent, id, title, pos, size, style) {

  //m_AuiMgr.SetManagedWindow(this);

  HICON hIcon = ::LoadIcon(__gpHinstance, MAKEINTRESOURCE(IDC_LOGO));
  if (hIcon) {
   ::SendMessageW(GetHWND(), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
   ::SendMessageW(GetHWND(), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
  }

  m_pMenuMain = new wxMenuBar();
  auto menu_about = new wxMenu();
  menu_about->Append(wxID_ABOUT);
  m_pMenuMain->Append(menu_about, _("&About"));
  wxFrameBase::SetMenuBar(m_pMenuMain);

#if 0
  m_pToolbarMain = wxFrameBase::CreateToolBar(wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL);
  wxFrameBase::SetToolBar(m_pToolbarMain);

  m_pStatusbarMain = wxFrameBase::CreateStatusBar();
  m_pStatusbarMain->SetStatusText(_("Ready"));
  wxFrameBase::SetStatusBar(m_pStatusbarMain);
#endif

  //m_pTreeCtrlMain = new TreeCtrlMain(this);

  //wxRect rtClient = GetClientRect();
  //m_pTreeCtrlMain->SetSize(108, rtClient.GetHeight());
  m_pChildConfig = new IChildConfigure(this);
  m_pChildConfig->Maximize();
  //m_pChildConfig->SetSize(500, 500);
  m_pChildConfig->Show();
  //m_pChildConfigure->Update();
  //m_pTreeCtrlMain = new TreeCtrlMain(this);
  //auto tree = new TreeCtrlMain(this);
  //m_AuiMgr.AddPane(
  // tree,
  // wxAuiPaneInfo().Layer(1).Row(1).Position(0).CloseButton(false).MaxSize(110, 0).Left().Maximize());

  //auto window = new wxTextCtrl(
  // this, wxID_ANY, wxString("asdflkhasglhasdg"));
  //m_AuiMgr.AddPane(window, 
  // wxAuiPaneInfo().Layer(1).Row(1).Position(1).CloseButton(false).Right().Maximize());

  //m_AuiMgr.AddPane(new wxWindow, wxAuiPaneInfo().
  // /*Name("test9").Caption("Text Pane with Hide Prompt").*/
  // Right().Layer(0).Position(2).Maximize().CloseButton(false).CenterPane());


  //m_AuiMgr.Update();
 }

 IMDIParentFrame::~IMDIParentFrame() {
  for (wxWindowList::const_iterator i = GetChildren().begin();
   i != GetChildren().end();
   ++i)
  {
   if (wxDynamicCast(*i, wxMDIChildFrame))
    (*i)->Close();
  }
 }

 void IMDIParentFrame::OnSize(wxSizeEvent& wxEvent) {
  if (m_pChildConfig)
   m_pChildConfig->SetSize(GetClientSize());

  wxEvent.Skip();
 }
 void IMDIParentFrame::OnClose(wxCloseEvent& wxEvent) {
#if 0
  int res = wxMessageBox(
   "Are you sure you want to exit system?",
   "tip",
   wxYES_NO,
   this);
  if (res != wxYES) {
   wxEvent.Veto();
  }
  else {
   auto handle = wxApp::GetInstance();
   if (handle)
    wxQueueEvent(handle, new wxThreadEvent(wxEVT_THREAD, shared::wx::WX_CMD_ONAPPDESTORY));
   wxEvent.Skip();
  }
#endif

  auto handle = wxApp::GetInstance();
  if (handle)
   wxQueueEvent(handle, new wxThreadEvent(wxEVT_THREAD, shared::wx::WX_CMD_ONAPPDESTORY));
  wxEvent.Skip();
 }


 void IMDIParentFrame::OnAbout(wxCommandEvent& WXUNUSED(evt)) {
#if 0
  wxAboutDialogInfo info;
  info.SetName(_("A tool for managing traffic servers."));
  info.SetDescription(_("This tool may not be copied or circulated without the permission of the developer!"));
  info.SetCopyright("(C) 2008-2022 Martell.");
  info.AddDeveloper("_ _ _ www.skstu.com _ _ _");
#endif
  wxAboutDialogInfo info;
  info.SetVersion(L"1.0.0.1");
  info.SetName(L"Google Chromium kernel browser fingerprint project.");
  info.SetDescription(L"This software may not be copied or circulated without the permission of the developer!");
  info.SetCopyright(L"Memade® Corporation. All rights reserved.");
  info.AddDeveloper(L"Martell");
  wxAboutBox(info, this);
 }

 WXLRESULT IMDIParentFrame::MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) {
  switch (nMsg) {
  case WM_CLOSE: {
   if (!::IsWindow(m_hWnd))
    break;
   ::ShowWindow(m_hWnd, SW_HIDE);
   return TRUE;
  }break;
  default:
   break;
  }
  return __super::MSWWindowProc(nMsg, wParam, lParam);
 }
}///namespace local