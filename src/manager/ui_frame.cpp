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
  m_pTreeviewMain = dynamic_cast<ui::TreeView*>(FindControl(L"treeview_main"));
  m_pTabboxMain = dynamic_cast<ui::TabBox*>(FindControl(L"tabbox_main"));
  m_pBtnSystemClose = dynamic_cast<ui::Button*>(FindControl(L"btn_system_close"));
  m_pBtnSystemMax = dynamic_cast<ui::Button*>(FindControl(L"maxbtn"));
  m_pBtnSystemMin = dynamic_cast<ui::Button*>(FindControl(L"minbtn"));
  m_pBtnBrowserConfigSave = dynamic_cast<ui::Button*>(FindControl(L"btn_browser_config_save"));
  m_pBtnBrowserConfigCreate = dynamic_cast<ui::Button*>(FindControl(L"btn_browser_config_create"));
  m_pBtnBrowserConfigRemove = dynamic_cast<ui::Button*>(FindControl(L"btn_browser_config_remove"));
  m_pListboxUserBrowserConfig = decltype(m_pListboxUserBrowserConfig)(FindControl(L"listbox_browser_config"));
  m_pUserBrowserConfigPage = decltype(m_pUserBrowserConfigPage)(FindControl(L"box_user_browser_config_page"));
  if (m_pUserBrowserConfigPage) {
   auto found_item = (ui::CheckBox*)m_pUserBrowserConfigPage->FindSubControl(L"proxy_enable");
   if (found_item) {
    found_item->AttachSelect(nbase::Bind(&UIFrame::OnCheckProxySelected, this, std::placeholders::_1));
    found_item->AttachUnSelect(nbase::Bind(&UIFrame::OnCheckProxyUnSelected, this, std::placeholders::_1));
   }
  }
  m_pBtnBrowserStartProgram = decltype(m_pBtnBrowserStartProgram)(FindControl(L"btn_browser_config_start"));
  if(m_pTreeviewMain)
   m_pTreeviewMain->SelectItem(0);

  auto UserBrowserConfigsSnapshoot = Global::ConfigGet()->UserBrowserConfigsSnapshoot();
  for (const auto& config : UserBrowserConfigsSnapshoot) {
   m_pListboxUserBrowserConfig->CreateUserBrowserConfigItem(config);
  }

  m_pBtnBrowserStartProgram->AttachClick(nbase::Bind(&UIFrame::OnBtnBrowserConfigStart, this, std::placeholders::_1));
  m_pBtnBrowserConfigSave->AttachClick(nbase::Bind(&UIFrame::OnBtnBrowserConfigSave, this, std::placeholders::_1));
  m_pListboxUserBrowserConfig->AttachSelect(nbase::Bind(&UIFrame::OnListboxUserBrowserConfigSelected, this, std::placeholders::_1));
  m_pBtnBrowserConfigCreate->AttachClick(nbase::Bind(&UIFrame::OnBtnBrowserConfigCreate, this, std::placeholders::_1));
  m_pBtnBrowserConfigRemove->AttachClick(nbase::Bind(&UIFrame::OnBtnBrowserConfigRemove, this, std::placeholders::_1));

  m_pLabelSystemTitle->SetText(MAIN_WINDOW_TITLE);
  m_pTreeviewMain->AttachSelect(nbase::Bind(&UIFrame::OnTreeViewSelected, this, std::placeholders::_1));
  m_pBtnSystemClose->AttachClick(nbase::Bind(&UIFrame::OnBtnSystemClose, this, std::placeholders::_1));

  if (m_pListboxUserBrowserConfig->GetCount() > 0)
   m_pListboxUserBrowserConfig->SelectItem(0);
 }
 LRESULT UIFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  return __super::OnClose(uMsg, wParam, lParam, bHandled);
 }
 LRESULT UIFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  PostQuitMessage(0L);
  return __super::OnDestroy(uMsg, wParam, lParam, bHandled);
 }


}///namespace local