#include "stdafx.h"

namespace local {
 bool UIFrame::OnListboxUserBrowserConfigSelected(ui::EventArgs* args) {
  auto current_selete_index = decltype(m_pListboxUserBrowserConfig)(args->pSender)->GetCurSel();
  auto current_select_item = (UIUserBrowserConfigListItem*)decltype(m_pListboxUserBrowserConfig)(args->pSender)->GetItemAt(current_selete_index);
  if (!m_pUserBrowserConfigPage->IsVisible())
   m_pUserBrowserConfigPage->SetVisible(true);
  std::string config = Global::ConfigGet()->GetUserBrowserConfig(current_select_item->Identify());
  return *m_pUserBrowserConfigPage << config;
 }
 bool UIFrame::OnTreeViewSelected(ui::EventArgs* args) {
  m_pTabboxMain->SelectItem(decltype(m_pTreeviewMain)(args->pSender)->GetCurSel());
  return true;
 }

 bool UIFrame::OnBtnSystemClose(ui::EventArgs* args) {
  nim_comp::ShowMsgBox(m_hWnd,
   [&](nim_comp::MsgBoxRet ret) {
    if (nim_comp::MsgBoxRet::MB_YES == ret) {
     ::SendMessageW(m_hWnd, WM_CLOSE, 0, 0);
    }
   },
   L"您确定需要退出系统吗？", false,
    MAIN_WINDOW_TITLE, false,
    L"确定", false,
    L"返回", false);
  return true;
 }

 bool UIFrame::OnBtnBrowserConfigCreate(ui::EventArgs* args) {
  std::string default_config;
  m_pUserBrowserConfigPage->GenerateDefaultConfig(default_config);
  m_pListboxUserBrowserConfig->CreateUserBrowserConfigItem(default_config);
  return m_pListboxUserBrowserConfig->SelectItem(0);
 }
 bool UIFrame::OnBtnBrowserConfigRemove(ui::EventArgs* args) {
  bool result = false;
  do {
   result = m_pListboxUserBrowserConfig->RemoveUserBrowserConfigItem();
   if (!result)
    break;
   if (Global::ConfigGet()->UserBrowserConfigEmpty())
    m_pUserBrowserConfigPage->SetVisible(false);
  } while (0);
  return result;
 }
 bool UIFrame::OnBtnBrowserConfigSave(ui::EventArgs* args) {
  bool result = false;
  do {
   if (!m_pUserBrowserConfigPage)
    break;
   auto item_cursel = m_pListboxUserBrowserConfig->GetCurSel();
   if (item_cursel < 0)
    break;
   auto pCurSelConfig = (UIUserBrowserConfigListItem*)m_pListboxUserBrowserConfig->GetItemAt(item_cursel);
   std::string save_data = m_pUserBrowserConfigPage->OutputConfig(pCurSelConfig->Identify());
   if (save_data.empty())
    break;
   auto cursel = m_pListboxUserBrowserConfig->GetCurSel();
   if (cursel >= 0) {
    auto item = (UIUserBrowserConfigListItem*)m_pListboxUserBrowserConfig->GetItemAt(cursel);
    *item << save_data;
    *item >> m_pUserBrowserConfigPage;
    item->SetTitle(m_pUserBrowserConfigPage->GetName());
   }
   Global::ConfigGet()->PushUserBrowserConfig(save_data);
   result = true;
  } while (0);

  nim_comp::ShowMsgBox(m_hWnd,
   [&](nim_comp::MsgBoxRet ret) {
    if (nim_comp::MsgBoxRet::MB_YES == ret) {

    }
   },
   std::format(L"保存修改{}!", result ? L"成功" : L"失败"), false,
    L"提示",
    false,
    L"确定", false,
    L"", false);

  return result;
 }

 bool UIFrame::OnBtnBrowserConfigStart(ui::EventArgs* args) {
  bool result = false;
  do {
   std::string browser_startup_cmdline;
   std::string browser_pathname = shared::Win::GetModulePathA() + R"(\Browser\chrome.exe)";
#if _DEBUG
   browser_pathname = R"(D:\Demo\Browser\chrome.exe)";
#endif

   std::uint64_t identify = 0;
   do {
    auto cursel_item_idx = m_pListboxUserBrowserConfig->GetCurSel();
    if (cursel_item_idx < 0)
     break;
    auto cursel_item = (UIUserBrowserConfigListItem*)m_pListboxUserBrowserConfig->GetItemAt(cursel_item_idx);

    identify = cursel_item->Identify();
   } while (0);
   if (identify <= 0)
    break;

   std::string current_config_path = shared::Win::PathFixedA(\
    shared::Win::GetModulePathA() + R"(\Configs\)" + std::to_string(identify) + R"(\)");
   //!@ 创建插件运行时目录配置
   shared::Win::CreateDirectoryA(current_config_path);
   
   do {//!@ 跳转URL
    if (!m_pUserBrowserConfigPage)
     break;
    std::string url = shared::IConv::WStringToMBytes(m_pUserBrowserConfigPage->GetJumpUrl());
    if (url.empty())
     break;
    browser_startup_cmdline.append(" ").append(url);
   } while (0);
  
   do {//!@ 如果启用的扩展 
    if (!m_pUserBrowserConfigPage->GetProxyEnable())
     break;
    std::string extension_dir = shared::Win::PathFixedA(current_config_path + "\\Extensions\\AutoProxy\\");
    std::string extension_release_dir = shared::Win::PathFixedA(current_config_path + "\\Extensions\\");
    std::string proxy_account, proxy_address, proxy_password;
    proxy_address = shared::IConv::WStringToMBytes(m_pUserBrowserConfigPage->GetProxyAddress());
    proxy_account = shared::IConv::WStringToMBytes(m_pUserBrowserConfigPage->GetProxyAccount());
    proxy_password = shared::IConv::WStringToMBytes(m_pUserBrowserConfigPage->GetProxyPassword());
    if (proxy_address.empty() || proxy_account.empty() || proxy_password.empty())
     break;
    std::string proxy_extension_res = shared::Win::Resource::Load(__gpHinstance, IDR_CHROMIUM_EXTENSIONS_AUTOPROXY, "ZIP");
    shared::Zip::zipBufferUnCompress(proxy_extension_res,
     [&](const std::string&, const std::string&, bool&) ->bool {
      return true;
     }, extension_release_dir);

    //!@ 处理代理扩展帐户

    do {//!@ AutoProxy
     std::string change_target_file = extension_dir + "bg.js";
     if (!shared::Win::AccessA(change_target_file))
      break;
     std::string change_target_file_buffer = shared::Win::File::Read(change_target_file);
     if (change_target_file_buffer.empty())
      break;
     do {
      auto begin = change_target_file_buffer.find(R"(var login=")");
      if (begin == std::string::npos)
       break;
      auto end = change_target_file_buffer.find(";", begin);
      std::string code_line = change_target_file_buffer.substr(begin, end - begin);
      std::string login = std::format(R"(var login="{}")", proxy_account);
      change_target_file_buffer.replace(begin, code_line.size(), login);
     } while (0);

     do {
      auto begin = change_target_file_buffer.find(R"(var password=")");
      if (begin == std::string::npos)
       break;
      auto end = change_target_file_buffer.find(";", begin);
      std::string code_line = change_target_file_buffer.substr(begin, end - begin);
      std::string password = std::format(R"(var password="{}")", proxy_password);
      change_target_file_buffer.replace(begin, code_line.size(), password);
     } while (0);
     shared::Win::File::Write(change_target_file, change_target_file_buffer);
    } while (0);
    

    browser_startup_cmdline.append(" --load-extension=")
     .append(extension_dir);

    browser_startup_cmdline.append(std::format(R"( --proxy-server="{}")", proxy_address));
   } while (0);



    browser_startup_cmdline.append(shared::Win::PathFixedA(std::format(R"( --user-data-dir={} --profile-directory=Default)",
     current_config_path + "\\browser_caches\\"
    )));


   auto ua = m_pUserBrowserConfigPage->GetUserAgent();
   if (!ua.empty()) {
    browser_startup_cmdline.append(std::format(R"( --user-agent="{}")", shared::IConv::WStringToMBytes(ua)));
   }


   do {//!@ 创建插件配置
    std::string config = Global::ConfigGet()->GetUserBrowserConfig(identify);
    if (config.empty())
     break;
    std::string plugin_config_pathname = shared::Win::PathFixedA(current_config_path + "\\config.json");
    shared::Win::File::Write(plugin_config_pathname, config);
    browser_startup_cmdline.append(std::format(R"( --load-plugin={})",plugin_config_pathname));
   } while (0);


   shared::Win::Process::CreateA(
    browser_pathname,
    browser_startup_cmdline, 
    [](const HANDLE&, const DWORD&) {}
   );

   result = true;
  } while (0);
  return result;
 }
 bool UIFrame::OnCheckProxyUnSelected(ui::EventArgs* args) {
  bool result = false;
  do {
   if (!m_pUserBrowserConfigPage)
    break;
   m_pUserBrowserConfigPage->ProxyCtrlEnable(false);
   result = true;
  } while (0);
  return result;
 }
 bool UIFrame::OnCheckProxySelected(ui::EventArgs* args) {
  bool result = false;
  do {
   if (!m_pUserBrowserConfigPage)
    break;
   m_pUserBrowserConfigPage->ProxyCtrlEnable(true);
   result = true;
  } while (0);
  return result;
 }





#if 0
 void Manager::OnCheckSelectChanged(CControlUI* pSender) {
  if (pSender->GetName() == L"B288520F85B6") {// 代理开关
   if (((CCheckBoxUI*)pSender)->IsSelected()) {
    GetCtrl<CControlUI>(L"4E120C0F957B")->SetEnabled(true);
    GetCtrl<CControlUI>(L"0C9DAC6E6D51")->SetEnabled(true);
    GetCtrl<CControlUI>(L"5DFAF388FD1F")->SetEnabled(true);
   }
   else {
    GetCtrl<CControlUI>(L"4E120C0F957B")->SetEnabled(false);
    GetCtrl<CControlUI>(L"0C9DAC6E6D51")->SetEnabled(false);
    GetCtrl<CControlUI>(L"5DFAF388FD1F")->SetEnabled(false);
   }
  }


 }
 void Manager::OnBtnStartupBrowser(CControlUI* pSender) {
  do {
   bool found = false;
   CControlUI* pos = pSender;
   do {
    if (!pos)
     break;
    if (!pos->GetName().Compare(_T("7B6D0CA7904D"))) {
     found = true;
     break;
    }
    pos = pos->GetParent();
   } while (1);

   if (!found)
    break;

   auto page = (UIBrowserConfigPage*)pos;
   if (!page)
    break;

   bool proxy_enable = GetCtrl<CCheckBoxUI>(L"B288520F85B6")->IsSelected();

   std::string starup_cmdline;

   std::string jump_url = page->GetJumpUrl();
   std::string UserAgent = R"(Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36 Edg/110.0.1587.46)";
   std::string user_data_dir = shared::Win::GetModulePathA() +
    "BrowserCache\\" + std::to_string(shared::Win::Time::TimeStamp<std::chrono::milliseconds>());

   std::string memade_cmd;

   if (proxy_enable) {
    std::string proxy_address = page->GetProxyAddress();
    std::string proxy_account = page->GetProxyAccount();
    std::string proxy_password = page->GetProxyPassword();
    //--memade={}
    //shared::Encryption::base64::base64_encode(std::format("--os_ubr={} --browser_ver={}", os_version, browser_version)
    //--proxy-server="liyz888-zone-custom-region-us-session-86977717-sessTime-60:c646674de314d7f2@proxy.ipidea.io:2333"
    std::string cmd_proxy_node = std::format(R"({}:{}@{})", proxy_account, proxy_password, proxy_address);
    std::string cmd_proxy_current = std::format(R"({}:{}@{})", proxy_account, proxy_password, proxy_address);

    starup_cmdline = \
     std::format(R"(--user-data-dir={} --profile-directory=Default --proxy-server={} {})",
      user_data_dir,
      proxy_address,
      jump_url
     );

    starup_cmdline.append(" --load-extension=").append(
#if _DEBUG
     R"(D:\github\ChromiumBrowserRelease\Browser\Extensions\AutoProxy)"
#else
     shared::Win::GetModulePathA() + "Extensions\\AutoProxy\\"
#endif
    );
    //!@ append memade cmdline parameters.
    //! 
    //! 
    memade_cmd = "--memade=";
    do {
     rapidjson::Document doc(rapidjson::kObjectType);

     rapidjson::Value proxy_node(rapidjson::kObjectType);
     proxy_node.AddMember("Enable", rapidjson::Value().SetBool(true).Move(), doc.GetAllocator());
     proxy_node.AddMember("ProxyAddress",
      rapidjson::Value().SetString(proxy_address.c_str(), doc.GetAllocator()).Move(), doc.GetAllocator());
     proxy_node.AddMember("ProxyAccount",
      rapidjson::Value().SetString(proxy_account.c_str(), doc.GetAllocator()).Move(), doc.GetAllocator());
     proxy_node.AddMember("ProxyPassword",
      rapidjson::Value().SetString(proxy_password.c_str(), doc.GetAllocator()).Move(), doc.GetAllocator());
     doc.AddMember("Proxy", proxy_node, doc.GetAllocator());
     memade_cmd.append(shared::Encryption::base64::base64_encode(shared::Json::toString(doc)));
    } while (0);
   }
   else {
    starup_cmdline = \
     std::format(R"(--user-data-dir={} --profile-directory=Default {})",
      user_data_dir,
      jump_url
     );
   }

   auto ua_enable = GetCtrl<CCheckBoxUI>(L"8253E31497F8")->IsSelected();
   if (ua_enable) {
    starup_cmdline.append(std::format(R"( --user-agent="{}")", UserAgent));
   }

   if (!memade_cmd.empty()) {
    starup_cmdline.append(" ").append(memade_cmd);
   }

   shared::Win::Process::CreateA(
#if _DEBUG
    R"(D:\github\ChromiumBrowserRelease\Browser\chrome.exe)",
#else
    shared::Win::GetModulePathA() + R"(\Browser\chrome.exe)",
#endif
    starup_cmdline, [](const HANDLE&, const DWORD&) {}
   );

  } while (0);
 }
 void Manager::OnSelectBrowserConfig(CControlUI* pSender) {
  m_pUITablayoutPageBrowserConfig->SelectItem(((UIBrowserConfigList*)pSender)->GetCurSel());
 }
 void Manager::OnBtnAppendBrowserConfig(CControlUI* pSender) {
  const char CreateConfigName[] = "新建配置";
  auto node = UIBrowserConfigListNode::Create();
  node->SetTitle(CreateConfigName);
  m_pUIListBrowserConfig->UnSelectAllItems();
  auto add_index = m_pUIListBrowserConfig->GetCount();
  m_pUIListBrowserConfig->AddAt(node, add_index);
  m_pUIListBrowserConfig->SelectItem(add_index);

  auto page = UIBrowserConfigPage::Create();
  //page->SetManager(&m_pm, m_pUITablayoutPageBrowserConfig);
  page->SetName(CreateConfigName);
  m_pUITablayoutPageBrowserConfig->AddAt(page, add_index);


  std::string config_json_data;
  *page >> config_json_data;
  auto sss = 0;
  }
 void Manager::OnBtnRemoveBrowserConfig(CControlUI* pSender) {

 }
 void Manager::OnBtnSaveBrowserConfig(CControlUI* pSender) {

 }
#endif
 }///namespace local