#include "stdafx.h"

namespace local {
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 UICefFrame::UICefFrame() :
  ICefFrame(IDI_MAIN, true) {

 }

 UICefFrame::~UICefFrame() {

 }
 ui::Control* UICefFrame::CreateControl(const std::wstring& pstrClass) {
  // 扫描 XML 发现有名称为 CefControl 的节点，则创建一个 ui::CefControl 控件
  if (pstrClass == L"CefControl") {
   if (nim_comp::CefManager::GetInstance()->IsEnableOffsetRender())
    return new nim_comp::CefControl;
   else
    return new nim_comp::CefNativeControl;
  }
  return nullptr;
 }
 void UICefFrame::InitWindow() {
  // 监听鼠标单击事件
  m_pRoot->AttachBubbledEvent(ui::kEventClick, nbase::Bind(&UICefFrame::OnClicked, this, std::placeholders::_1));
  // 从 XML 中查找指定控件
  m_pCefMainLocal = dynamic_cast<nim_comp::CefControlBase*>(FindControl(L"cef_control_local"));
  m_pCefMainLocal->LoadURL(
#if _DEBUG
   LR"(D:\__Github__\Windows\projects\browser_plugins\src\manager_site\res\script_js\jstest3.html)"
#else
   shared::Win::GetModulePathW() + LR"(\jstest3.html)"
#endif
  );

  auto btn = dynamic_cast<ui::Button*>(FindControl(L"c2j_getdata_test_button"));
  btn->AttachClick(nbase::Bind(&UICefFrame::OnBtnc2jtest, this, std::placeholders::_1));

  m_pCefMainLocal->AttachLoadEnd(nbase::Bind(&UICefFrame::OnLoadEndLocal, this, std::placeholders::_1));
  m_pCefMainLocal->AttachLoadStart(nbase::Bind(&UICefFrame::OnLoadBeginLocal, this));

  m_pCefMain = dynamic_cast<nim_comp::CefControlBase*>(FindControl(L"cef_control_remote"));
  m_pCefMain->AttachLoadStart(nbase::Bind(&UICefFrame::OnLoadBegin, this));
  m_pCefMain->AttachLoadEnd(nbase::Bind(&UICefFrame::OnLoadEnd, this, std::placeholders::_1));
  //m_pCefMain->LoadURL(L"http://main.tcsamples.com/");
  m_pCefMain->LoadURL(L"https://pixelscan.net/");
#if 0
  if (!nim_comp::CefManager::GetInstance()->IsEnableOffsetRender())
   cef_control_dev_->SetVisible(false);
  // 打开开发者工具
//cef_control_->AttachDevTools(cef_control_dev_);
// 加载皮肤目录下的 html 文件
//cef_control_->LoadURL(nbase::win32::GetCurrentModuleDirectory() + L"resources\\themes\\default\\cef\\cef.html");
#endif
 }
 LRESULT UICefFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  nim_comp::CefManager::GetInstance()->PostQuitMessage(0L);
  return __super::OnClose(uMsg, wParam, lParam, bHandled);
 }
 bool UICefFrame::OnNavigate(ui::EventArgs* msg) {
#if 0
  if (!edit_url_->GetText().empty()) {
   cef_control_->LoadURL(edit_url_->GetText());
   cef_control_->SetFocus();
  }
#endif
  return true;
 }

 void UICefFrame::OnLoadBegin() {


  auto sk = 0;
 }

 void UICefFrame::OnLoadBeginLocal() {
  //!@ 注册js调用方法[j2cOpenProcess]
  m_pCefMainLocal->RegisterCppFunc(L"j2cOpenProcess",
   ToWeakCallback(
    [this](const std::string& params, nim_comp::ReportResultFunction callback) {
     do {
      std::wstring params_unicode = nbase::UTF8ToUTF16(params);
      std::string params_ansi = shared::IConv::WStringToMBytes(params_unicode);
     } while (0);

     std::wstring recv_param =
      std::format(L"接收参数:[{}]", nbase::UTF8ToUTF16(params));

     nim_comp::Toast::ShowToast(recv_param, 5000, GetHWND());

     rapidjson::Document doc{ rapidjson::kObjectType };

     doc.AddMember(
      rapidjson::Value().SetString("program_pathname", doc.GetAllocator()).Move(),
      rapidjson::Value().SetString(R"(C:\Windows\System32\calc.exe)",doc.GetAllocator()).Move(),
      doc.GetAllocator()
     );

     bool open_result = false;
     shared::Win::Process::CreateA(R"(C:\Windows\System32\calc.exe)", "", 
      [&](const HANDLE&, const DWORD& processId) {     
       doc.AddMember(
        rapidjson::Value().SetString("process_id", doc.GetAllocator()).Move(),
        rapidjson::Value().SetUint(processId).Move(),
        doc.GetAllocator()
       );
     open_result = true;
      });

     doc.AddMember(
      rapidjson::Value().SetString("result", doc.GetAllocator()).Move(),
      rapidjson::Value().SetBool(open_result).Move(),
      doc.GetAllocator()
     );
     callback(false, shared::IConv::MBytesToUTF8(shared::Json::toString(doc)));
     //callback(false, shared::IConv::WStringToUTF8(LR"({ "message": "C端 : [j2cOpenProcess]方法调用成功 !" })"));
    }));
#if 0
  m_pCefMainLocal->RegisterCppFunc(L"ShowMessageBox",
   ToWeakCallback(
    [this](const std::string& params, nim_comp::ReportResultFunction callback) {
     nim_comp::Toast::ShowToast(nbase::UTF8ToUTF16(params), 3000, GetHWND());
  callback(false, R"({ "message": "Success." })");
    }));
#endif
 }

 void UICefFrame::OnLoadEndLocal(int httpStatusCode) {
  do {
   if (httpStatusCode != 0)
    break;

#if 0
   //!@ 页面加载完成后 调用js方法测试
   m_pCefMainLocal->CallJSFunction(L"c2jGetData",
    LR"({ "message": "C端 : 调用js [c2jGetData]" })",
    [this](const std::string& jsResult) {

     auto sksks = 0;
    },
    LR"()"/*javascript frame name*/);
#endif
  } while (0);
 }
 bool UICefFrame::OnBtnc2jtest(ui::EventArgs* args) {
  m_pCefMainLocal->CallJSFunction(L"c2jGetData",
   LR"({ "message": "C端 : 调用js [c2jGetData]" })",
   [this](const std::string& jsResult) {

    auto sksks = 0;
   },
   LR"()"/*javascript frame name*/);
  return true;
 }
 void UICefFrame::OnLoadEnd(int httpStatusCode) {
#if 0
  FindControl(L"btn_back")->SetEnabled(cef_control_->CanGoBack());
  FindControl(L"btn_forward")->SetEnabled(cef_control_->CanGoForward());
#endif
#if 0
  // 注册一个方法提供前端调用
  m_pCefMainRemote->RegisterCppFunc(L"ShowMessageBox",
   ToWeakCallback(
    [this](const std::string& params, nim_comp::ReportResultFunction callback) {
     nim_comp::Toast::ShowToast(nbase::UTF8ToUTF16(params), 3000, GetHWND());
  callback(false, R"({ "message": "Success." })");
    }));
#endif

  auto sk = 0;
 }

 bool UICefFrame::OnClicked(ui::EventArgs* msg) {
#if 0
  std::wstring name = msg->pSender->GetName();
  if (name == L"btn_dev_tool")
  {
   if (m_pCefMainRemote->IsAttachedDevTools())
   {
    m_pCefMainRemote->DettachDevTools();
   }
   else
   {
    m_pCefMainRemote->AttachDevTools(cef_control_dev_);
   }

   if (nim_comp::CefManager::GetInstance()->IsEnableOffsetRender())
   {
    m_pCefMainRemote->SetVisible(m_pCefMainRemote->IsAttachedDevTools());
   }
  }
  else if (name == L"btn_back")
  {
   cef_control_->GoBack();
  }
  else if (name == L"btn_forward")
  {
   cef_control_->GoForward();
  }
  else if (name == L"btn_navigate")
  {
   OnNavigate(nullptr);
  }
  else if (name == L"btn_refresh")
  {
   cef_control_->Refresh();
  }
#endif
  return true;
 }
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
  if (m_pTreeviewMain)
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