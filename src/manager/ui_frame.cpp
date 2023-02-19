#include "stdafx.h"

namespace local {

 UIFrame::UIFrame() : IFrame(IDI_MAIN, true) {

 }

 UIFrame::~UIFrame() {

 }

 void UIFrame::Release() const {
  delete this;
 }
 void UIFrame::InitWindow() {
  m_pLabelSystemTitle = dynamic_cast<ui::Label*>(FindControl(L"label_system_title"));
  m_pTreeMain = dynamic_cast<ui::TreeView*>(FindControl(L"tree_main"));
  m_pTabMain = dynamic_cast<ui::TabBox*>(FindControl(L"tab_main"));
  m_pBtnSystemClose = dynamic_cast<ui::Button*>(FindControl(L"btn_system_close"));
  m_pBtnSystemMax = dynamic_cast<ui::Button*>(FindControl(L"maxbtn"));
  m_pBtnSystemMin = dynamic_cast<ui::Button*>(FindControl(L"minbtn"));
  m_pBtnBrowserConfigCreate = dynamic_cast<ui::Button*>(FindControl(L"btn_browser_config_create"));
  m_pBtnBrowserConfigRemove = dynamic_cast<ui::Button*>(FindControl(L"btn_browser_config_remove"));


  m_pBtnBrowserConfigCreate->AttachClick(nbase::Bind(&UIFrame::OnBtnBrowserConfigCreate, this, std::placeholders::_1));
  m_pBtnBrowserConfigRemove->AttachClick(nbase::Bind(&UIFrame::OnBtnBrowserConfigRemove, this, std::placeholders::_1));

  m_pLabelSystemTitle->SetText(MAIN_WINDOW_TITLE);
  m_pTreeMain->AttachSelect(nbase::Bind(&UIFrame::OnTreeViewSelected, this, std::placeholders::_1));
  m_pBtnSystemClose->AttachClick(nbase::Bind(&UIFrame::OnBtnSystemClose, this, std::placeholders::_1));
 }
 LRESULT UIFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  return __super::OnClose(uMsg, wParam, lParam, bHandled);
 }
 LRESULT UIFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  PostQuitMessage(0L);
  return __super::OnDestroy(uMsg, wParam, lParam, bHandled);
 }


}///namespace local