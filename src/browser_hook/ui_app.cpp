#include "stdafx.h"

namespace local {
 wxIMPLEMENT_APP_NO_MAIN(IApp);

 IApp::IApp() {

 }
 IApp::~IApp() {
 }
 void IApp::RegisterAppInitEventCb(const shared::wx::tfAppInitEventCallback& cb) {
  m_AppInitEventCb = cb;
 }
 void IApp::RegisterAppCloseEventNotifyCb(const shared::wx::tfAppCloseEventNotifyCallback& cb) {
  m_AppCloseEventNotifyCb = cb;
 }
 void IApp::RegisterAppCreateFrameEventCb(const shared::wx::tfAppCreateFrameEventCallback& cb) {
  m_AppCreateFrameEventCb = cb;
 }
 bool IApp::OnInit() {
  bool result = false;
  do {
   if (!wxApp::OnInit())
    break;
   wxInitAllImageHandlers();
   wxAppBase::SetExitOnFrameDelete(false);
   wxEvtHandler::Bind(wxEVT_THREAD, &IApp::OnDestory, this, shared::wx::WX_CMD_ONAPPDESTORY);
   wxEvtHandler::Bind(wxEVT_THREAD, &IApp::OnCreateFrame, this, shared::wx::WX_CMD_ONAPPCREATEFRAME);
   result = true;
  } while (0);
  return result;
 }
 int IApp::OnExit() {
  int result = 0;
  do {


   result = wxApp::OnExit();
  } while (0);
  return result;
 }
 wxFrame* IApp::FrameGet() const {
  return m_pFrame;
 }
 void IApp::OnCreateFrame(wxThreadEvent& event) {
  auto obj = event.GetEventObject();
  if (obj) {
   m_pFrame = wxDynamicCast(obj, wxFrame);
  }
  else {
   m_pFrame = new IMDIParentFrame();
  }
#if _DEBUG
  m_pFrame->Show(true);
#else
  m_pFrame->Show(false);
#endif

  if (m_AppCreateFrameEventCb)
   m_AppCreateFrameEventCb(m_pFrame);
 }
 void IApp::OnDestory(wxThreadEvent& event) {
  ExitMainLoop();
 }


}///namespace local