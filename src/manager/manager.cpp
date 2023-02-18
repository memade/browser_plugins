#include "stdafx.h"

namespace local {

	Manager::Manager() {

	}

	Manager::~Manager() {
		SK_DELETE_PTR(m_pUIComboUserAgent);
	}
	void Manager::OnFinalMessage(HWND hWnd) {
		delete this;
	}
	bool Manager::Start() {
		do {
			if (m_IsOpen.load())
				break;
			m_hWnd = __super::Create(NULL, _TEXT("浏览器配置®"), UI_WNDSTYLE_FRAME, 0L);
			if (!m_hWnd)
				break;
			__super::CenterWindow();
			m_IsOpen.store(true);
		} while (0);
		return m_IsOpen.load();
	}
	void Manager::Stop() {
		do {
			if (!m_IsOpen.load())
				break;

			m_IsOpen.store(false);
		} while (0);
	}
	void Manager::CreateTray(PNOTIFYICONDATAW pNotifyIconData) {
		pNotifyIconData->cbSize = sizeof(*pNotifyIconData);
		pNotifyIconData->hWnd = m_hWnd;
		pNotifyIconData->uID = IDI_MAIN;
		pNotifyIconData->uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		pNotifyIconData->uCallbackMessage = shared::ui::WM_NOTIFYICONDATA_MESSAGE;
		pNotifyIconData->hIcon = ::LoadIconW(
			CPaintManagerUI::GetInstance(), MAKEINTRESOURCE(IDI_MAIN));
		::wcscpy_s(pNotifyIconData->szTip, MAIN_WINDOW_TITLE);
		::Shell_NotifyIconW(NIM_ADD, pNotifyIconData);
		//auto hMenu = CreatePopupMenu();//生成菜单
		////为托盘菜单添加两个选项
		//AppendMenu(hMenu, MF_STRING, ID_SHOW, TEXT("策略更新"));
		//AppendMenu(hMenu, MF_STRING, ID_RECORD, TEXT("管控记录"));
		//AppendMenu(hMenu, MF_STRING, ID_ABOUT, TEXT("关于"));
	}
	void Manager::DestoryTray(PNOTIFYICONDATAW pNotifyIconData) {
		::Shell_NotifyIconW(NIM_DELETE, pNotifyIconData);
	}
	void Manager::InitWindow() {
		//m_pComboParent = GetCtrl<CLabelUI>(L"1214BBFE3F42");
		//if (m_pUIComboUserAgent) {
		//	m_pUIComboUserAgent->SetManager(&m_pm, m_pComboParent);
		//}

		m_pMainWindowTitleUI = GetCtrl<CLabelUI>(L"8365FB6BFF98");
		m_pUITreeViewMain = GetCtrl<CTreeViewUI>(L"3E26C7C9ECF7");
		m_pUITablayoutMain = GetCtrl<CTabLayoutUI>(L"B2DD4CE4C568");
		m_pUITablayoutPageBrowserConfig = GetCtrl<CTabLayoutUI>(L"51C0375A6FA8");
		m_pUIListBrowserConfig = GetCtrl<UIBrowserConfigList>(L"1FFE474A7213");
		m_pUIListBrowserConfig->SetMultiSelect(false);

		if (m_pMainWindowTitleUI)
			m_pMainWindowTitleUI->SetText(MAIN_WINDOW_TITLE);

		if (m_pUITablayoutMain && m_pUITablayoutMain->GetCount() >= 2)
			m_pUITablayoutMain->SelectItem(1);

		if (m_pUITreeViewMain && m_pUITreeViewMain->GetCount() >= 2) {
			m_pUITreeViewMain->SelectItem(0);
		}

#if _DEBUG
		//for (int i = 0; i < 5; ++i) {
		//	auto node = UIBrowserConfigListNode::Create();
		//	node->SetTitle(std::format("测试配置({})", i));
		//	m_pUIListBrowserConfig->Add(node);
		//}


#endif

		//!@ test config list
		//! 
		//! 
		//UIBrowserConfigNode* pNode = m_pUIListBrowserConfig->AppendBrowserConfig();
#if 0
		pNode->SetUrl(R"(https://cn.bing.com/)");
		pNode->SetTitle("ProxyNode[中国上海] Version[100.0.0.0]");
		pNode->SetUserDataPath(R"(D:\BrowserCaches\Browser1)");
		pNode->SetOSVersion("100");
		pNode->SetBrowserVersion("100.0.0.0");

		pNode = m_pUIListBrowserConfig->AppendBrowserConfig();
		pNode->SetTitle("ProxyNode[乌干达] Version[100.0.0.0]");
		pNode->SetUrl(R"(https://www.baidu.com/)");
		pNode->SetUserDataPath(R"(D:\BrowserCaches\Browser2)");
		pNode->SetOSVersion("101");
		pNode->SetBrowserVersion("101.0.0.0");

		pNode = m_pUIListBrowserConfig->AppendBrowserConfig();
		pNode->SetTitle("ProxyNode[中国香港] Version[100.0.0.0]");
		pNode->SetUrl(R"(https://pixelscan.net/)");
		pNode->SetUserDataPath(R"(D:\BrowserCaches\Browser3)");
		pNode->SetOSVersion("102");
		pNode->SetBrowserVersion("102.0.0.0");
#endif
	}
	LRESULT Manager::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT Manager::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		m_pm.Init(GetHWND());
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(std::wstring(GetWindowClassName()).append(_TEXT(".xml")).c_str(), (LPCTSTR)0, this, &m_pm);
		ASSERT(pRoot && "Failed to parse 'ui.xml'");
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this);
		bHandled = TRUE;
		return 0;
	}

	LRESULT Manager::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT Manager::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	LRESULT Manager::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		switch (uMsg) {
		case WM_COMMAND: {
			switch (wParam) {
			case shared::ui::WM_NOTIFYICONDATA_MENU_EXIT: {
				::PostMessageW(GetHWND(), WM_CLOSE, 0, 0);
				return TRUE;
			}break;
			default:
				break;
			}
		}break;
		case shared::ui::WM_NOTIFYICONDATA_MESSAGE: {
			switch (lParam) {
			case WM_LBUTTONDBLCLK: {
				if (wParam != IDI_MAIN)
					break;
				if (::IsWindowVisible(GetHWND()))
					ShowWindow(false);
				else
					ShowWindow(true);
			}break;
			case WM_RBUTTONDOWN: {
				if (wParam != IDI_MAIN)
					break;
				POINT pt = { 0 };
				::GetCursorPos(&pt);
				::TrackPopupMenu(m_hTrayPopMenu, TPM_RIGHTBUTTON, pt.x, pt.y, NULL, GetHWND(), NULL);
			}break;
			default:
				break;
			}
		}break;
		default:
			break;
		}
		bHandled = FALSE;
		return 0;
	}
	LRESULT Manager::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	LRESULT Manager::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		bHandled = FALSE;
		return 0;
	}
	CControlUI* Manager::CreateControl(LPCTSTR pstrClassName) {
		CControlUI* result = nullptr;
#if 0
		if (_tcsicmp(pstrClassName, _T("UICombo")) == 0) {
			do {
				auto hComboBox = ::CreateWindowW(WC_COMBOBOX, TEXT(""),
					CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
					0, 0, 200, 200, m_pm.GetPaintWindow(), NULL, m_pm.GetInstance(),
					NULL);
				if (!hComboBox)
					break;
				result = new UICombo();
				((UICombo*)result)->Attach(hComboBox);
				//m_pm.AttachDialog(m_pUIComboUserAgent);
				//auto parent = GetCtrl<CControlUI>(L"1214BBFE3F42");
				//m_pUIComboUserAgent->SetManager(&m_pm, m_pComboParent);
			} while (0);
		}
#endif
		return result;
	}


}///namespace local