#include "stdafx.h"

namespace local {

 wxIMPLEMENT_APP_NO_MAIN(App);

 App::App() {

 }

 App::~App() {

 }

 bool App::OnInit() {
  bool result = false;
  do {
   if (!wxApp::OnInit())
    break;
   /*wxInitAllImageHandlers();
   wxAppBase::SetExitOnFrameDelete(false);*/

   result = true;
  } while (0);
  return result;
 }
 int App::OnExit() {
  int result = 0;
  do {

   result = wxApp::OnExit();
  } while (0);
  return result;
 }
 wxFrame* App::FrameGet() const {
  return m_pFrame;
 }

}