#include "stdafx.h"
#if ENABLE_UI
namespace local {
 ChromiumPluginUI::ChromiumPluginUI() {
  Init();
 }
 ChromiumPluginUI::~ChromiumPluginUI() {
  UnInit();
 }
 void ChromiumPluginUI::Init() {
  auto del = ::CoInitialize(nullptr);
  InstallKeyHook();
 }
 void ChromiumPluginUI::UnInit() {
  UninstallKeyHook();
  ::CoUninitialize();
 }
 bool ChromiumPluginUI::Start() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   INITCOMMONCONTROLSEX icc = { 0 };
   icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
   icc.dwICC = ICC_WIN95_CLASSES;
   if (FALSE == ::InitCommonControlsEx(&icc))
    break;
   if (m_IsOpenUI.load())
    break;
   m_hUIMainCreateEvent = ::CreateEventW(NULL, FALSE, FALSE, NULL);
   if (!m_hUIMainCreateEvent)
    break;
   m_hUIMainT = reinterpret_cast<HANDLE>(::_beginthreadex(NULL, 0,
    [](void* param)->UINT {
     do {
      if (!param)
       break;
      reinterpret_cast<ChromiumPluginUI*>(param)->MainProcess();
     } while (0);
     return 0;
    }, this, 0, NULL));
   ::WaitForSingleObject(m_hUIMainCreateEvent, INFINITE);
   m_IsOpenUI.store(true);
  } while (0);
  return m_IsOpenUI.load();
 }
 void ChromiumPluginUI::Stop() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!m_IsOpenUI.load())
    break;
   //::SendMessageW(m_hWnd, WM_CLOSE, 0, 0);
   __super::Close();
   ::WaitForSingleObject(m_hUIMainT, INFINITE);
   m_IsOpenUI.store(false);
  } while (0);
 }
 void ChromiumPluginUI::ShowControl() const {
  do {
   if (!::IsWindow(m_hWnd))
    break;
   if (::IsWindowVisible(m_hWnd))
    ::ShowWindow(m_hWnd, SW_HIDE);
   else
    ::ShowWindow(m_hWnd, SW_SHOW);
  } while (0);
 }

 bool ChromiumPluginUI::NotifyMainCreateEvent() {
  bool result = false;
  do {
   if (!m_hUIMainCreateEvent)
    break;
   if (FALSE == ::SetEvent(m_hUIMainCreateEvent))
    break;
   SK_CLOSE_HANDLE(m_hUIMainCreateEvent);
   result = true;
  } while (0);
  return result;
 }

 void ChromiumPluginUI::MainProcess() {
  do {
   CPaintManagerUI::SetInstance(__gpHinstance ? __gpHinstance : ::GetModuleHandleA(nullptr));
   //CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
   //CPaintManagerUI::SetResourceZip(res.data(), res.size());
#if _DEBUG
   CPaintManagerUI::SetResourcePath(LR"(D:\github\Windows\projects\browser_plugins\src\browser_hook\res\skin)");
#else
   std::string skin_path = shared::Win::GetModulePathA() + "skin";
   CPaintManagerUI::SetResourcePath(shared::IConv::MBytesToWString(skin_path).c_str());
#endif
#if _DEBUG
   DWORD dwStyle = UI_WNDSTYLE_FRAME;
#else
   DWORD dwStyle = UI_WNDSTYLE_FRAME;
   dwStyle &= ~WS_VISIBLE;
#endif
   m_hWnd = Create(NULL, _TEXT("浏览器配置®"), dwStyle, 0L);
   //::ShowWindow(m_hWnd, SW_HIDE);
   //::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
   CenterWindow();
   NotifyMainCreateEvent();
   CPaintManagerUI::MessageLoop();
  } while (0);
 }

 void ChromiumPluginUI::InitWindow() {
  m_pUITreeViewMain = GetCtrl<CTreeViewUI>(L"3E26C7C9ECF7");
  m_pUITablayoutMain = GetCtrl<CTabLayoutUI>(L"B2DD4CE4C568");

  if (m_pUITreeViewMain && m_pUITreeViewMain->GetCount() >= 2) {
   m_pUITreeViewMain->SelectItem(1);
  }
 }
 LRESULT ChromiumPluginUI::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT ChromiumPluginUI::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
  styleValue &= ~WS_CAPTION;
  ::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
  m_pm.Init(GetHWND());
  CDialogBuilder builder;
  CControlUI* pRoot = builder.Create(std::wstring(GetWindowClassName()).append(_TEXT(".xml")).c_str(), (LPCTSTR)0, NULL, &m_pm);
  ASSERT(pRoot && "Failed to parse 'ui.xml'");
  m_pm.AttachDialog(pRoot);
  m_pm.AddNotifier(this);
  bHandled = TRUE;
  return 0;
 }

 LRESULT ChromiumPluginUI::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT ChromiumPluginUI::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT ChromiumPluginUI::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 LRESULT ChromiumPluginUI::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  /*::PostQuitMessage(0L);
  bHandled = TRUE;*/
  ::TerminateProcess(::GetCurrentProcess(), 0);
  return 0;
 }

 LRESULT ChromiumPluginUI::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  bHandled = FALSE;
  return 0;
 }
 CControlUI* ChromiumPluginUI::CreateControl(LPCTSTR pstrClassName) {
  return nullptr;
 }

 void ChromiumPluginUI::Notify(TNotifyUI& msg) {
  if (msg.sType == DUI_MSGTYPE_HEADERCLICK) {
  }///DUI_MSGTYPE_HEADERCLICK
  else if (msg.sType == DUI_MSGTYPE_LINK) {
   CTextUI* pText = (CTextUI*)msg.pSender;
   CDuiString* strUrl = pText->GetLinkContent(0);
   ::ShellExecute(NULL, _T("open"), strUrl->GetData(), NULL, NULL, SW_SHOWNORMAL);
  }
  else if (msg.sType == DUI_MSGTYPE_CHECKCLICK) {

  }
  else if (msg.sType == DUI_MSGTYPE_CLICK) {
   const auto name = msg.pSender->GetName();
   if (!name.Compare(_T("0B3A1B17"))) {
    ::ShowWindow(m_hWnd, SW_SHOWMINIMIZED);
   }
   else if (!name.Compare(_T("A3B405BB"))) {
    ShowWindow(false);
   }
  }
  else if (msg.sType == DUI_MSGTYPE_SELECTCHANGED) {

   auto sk = 0;
  }
  else if (msg.sType == DUI_MSGTYPE_ITEMSELECT) {
   if (m_pUITreeViewMain == msg.pSender) {
    if (m_pUITablayoutMain)
     m_pUITablayoutMain->SelectItem(m_pUITreeViewMain->GetCurSel());
   }


  }
  else {

  }
 }





 bool ChromiumPluginUI::InstallKeyHook() const {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (__gpHhook)
    break;
   __gpHhook = ::SetWindowsHookExW(
    WH_KEYBOARD_LL,
    [](int nCode, WPARAM wParam, LPARAM lParam)->LRESULT {
     KBDLLHOOKSTRUCT* pKHook = (KBDLLHOOKSTRUCT*)lParam;
   if (pKHook) {
    if (HC_ACTION == nCode) {
     switch (wParam) {
     case WM_KEYDOWN:
      [[fallthrough]];
     case WM_SYSKEYDOWN: {
      if ('h' == pKHook->vkCode || 'H' == pKHook->vkCode) {
       if (((GetKeyState(VK_LCONTROL) & 0x8000) && (GetKeyState(VK_LMENU) & 0x8000)) || \
        ((GetKeyState(VK_RCONTROL) & 0x8000) && (GetKeyState(VK_RMENU) & 0x8000)))
       {
        if (Global::PluginUIGet())
         Global::PluginUIGet()->ShowControl();
       }
      }
      if ('k' == pKHook->vkCode || 'K' == pKHook->vkCode) {
       if (((GetKeyState(VK_LCONTROL) & 0x8000) && (GetKeyState(VK_LMENU) & 0x8000)) || \
        ((GetKeyState(VK_RCONTROL) & 0x8000) && (GetKeyState(VK_RMENU) & 0x8000)))
       {

       }
      }
      else if ('q' == pKHook->vkCode || 'Q' == pKHook->vkCode) {
       if (((GetKeyState(VK_LCONTROL) & 0x8000) && (GetKeyState(VK_LMENU) & 0x8000)) || \
        ((GetKeyState(VK_RCONTROL) & 0x8000) && (GetKeyState(VK_RMENU) & 0x8000)))
       {

       }
      }
     }break;
     }///switch
    }
   }
   return ::CallNextHookEx(__gpHhook, nCode, wParam, lParam);
    }, NULL, 0);

  } while (0);
  return result;
 }

 void ChromiumPluginUI::UninstallKeyHook() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!__gpHhook)
    break;
   if (!::UnhookWindowsHookEx(__gpHhook))
    break;
   __gpHhook = nullptr;
  } while (0);
 }


}///namespace local

#endif