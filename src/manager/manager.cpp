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
		case shared::ui::WM_NOTIFYICONDATA_MESSAGE: {

			UINT uID;//发出该消息的图标的ID
			UINT uMouseMsg;//鼠标动作
			POINT pt;
			uID = (UINT)wParam;
			uMouseMsg = (UINT)lParam;
			if (uMouseMsg == WM_LBUTTONDOWN)//如果是单击左键
			{
				switch (uID) {
				case IDI_MAIN:
					GetCursorPos(&pt);//取得鼠标位置
					//判断当前窗口是否为隐藏，隐藏就让其显示
					//if (AfxGetApp()->m_pMainWnd->IsIconic())
					//{
					//	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
					//}
					break;
				}
			}
			if (uMouseMsg == WM_LBUTTONDOWN)//如果是单击右键
			{
				switch (uID)
				{
				case IDI_MAIN:

					HMENU hMenu = CreatePopupMenu();//生成托盘菜单
					//为托盘菜单添加两个选项
					AppendMenuW(hMenu, MF_STRING, 0, TEXT("提示"));
					AppendMenuW(hMenu, MF_STRING, 1, TEXT("退出"));
#if 0	
					TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_LEFTALIGN, pt.x, pt.y);

					HMENU menu = ::CreateMenu();  //定义右键菜单对象
					GetCursorPos(&pt);   //获取当前鼠标位置
					::LoadMenu(CPaintManagerUI::GetInstance(),)
					menu.LoadMenu(IDR_TUOPAN_MENU);   //载入右键快捷菜单
					SetForegroundWindow();//放置在前面
					CMenu* pmenu;    //定义右键菜单指针
					pmenu = menu.GetSubMenu(0);      //该函数取得被指定菜单激活的下拉式菜单或子菜单的句柄
					ASSERT(pmenu != NULL);
					pmenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, pt.x, pt.y, this);   //在指定位置显示右键快捷菜单
					HMENU hmenu = pmenu->Detach();
					pmenu->DestroyMenu();
#endif
				}
			}
	

			auto sk = 0;
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
		if (_tcsicmp(pstrClassName, _T("UICombo")) == 0) {
			do {
				auto hComboBox = ::CreateWindowW(WC_COMBOBOX, TEXT(""),
					CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED /*| WS_VISIBLE*/,
					0, 0, 200, 200, m_pm.GetPaintWindow(), NULL, m_pm.GetInstance(),
					NULL);
				if (!hComboBox)
					break;
				m_pUIComboUserAgent = new UICombo();
				m_pUIComboUserAgent->Attach(hComboBox);
				//m_pm.AttachDialog(m_pUIComboUserAgent);
				//auto parent = GetCtrl<CControlUI>(L"1214BBFE3F42");
				//m_pUIComboUserAgent->SetManager(&m_pm, m_pComboParent);
			} while (0);
		}

		return nullptr;
	}


}///namespace local