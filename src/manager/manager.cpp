#include "stdafx.h"

namespace local {

	Manager::Manager() {

	}

	Manager::~Manager() {

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
	void Manager::InitWindow() {
		m_pUITreeViewMain = GetCtrl<CTreeViewUI>(L"3E26C7C9ECF7");
		m_pUITablayoutMain = GetCtrl<CTabLayoutUI>(L"B2DD4CE4C568");
		m_pUIListBrowserConfig = GetCtrl<UIBrowserConfigList>(L"1FFE474A7213");
		if (m_pUITablayoutMain && m_pUITablayoutMain->GetCount() >= 2)
			m_pUITablayoutMain->SelectItem(1);

		if (m_pUITreeViewMain && m_pUITreeViewMain->GetCount() >= 2) {
			m_pUITreeViewMain->SelectItem(0);
		}

		//!@ test config list
		//! 
		//! 
		UIBrowserConfigNode* pNode = m_pUIListBrowserConfig->AppendBrowserConfig();
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
		CControlUI* pRoot = builder.Create(std::wstring(GetWindowClassName()).append(_TEXT(".xml")).c_str(), (LPCTSTR)0, NULL, &m_pm);
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
		return nullptr;
	}

	void Manager::Notify(TNotifyUI& msg) {
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
				__super::Close();
			}
			else if (!name.Compare(_T("B6AAAB2D9465"))) {

				do {
					bool found = false;
					CControlUI* pos = msg.pSender;
					do {
						if (!pos)
							break;
						if (!pos->GetName().Compare(_T("C24C84325602"))) {
							found = true;
							break;
						}
						pos = pos->GetParent();
					} while (1);

					if (!found)
						break;

					auto pBrowserConfigNodeUI = (UIBrowserConfigNode*)pos;
					auto url = pBrowserConfigNodeUI->GetUrl();
					auto user_data_dir = pBrowserConfigNodeUI->GetUserDataPath();
					auto os_version = pBrowserConfigNodeUI->GetOSVersion();
					auto browser_version = pBrowserConfigNodeUI->GetBrowserVersion();

					std::string starup_cmdline = \
						std::format(R"(--user-data-dir={} --profile-directory=Default {} --memade={})", 
							user_data_dir, 
							url,
							shared::Encryption::base64::base64_encode(std::format("--os_ubr={} --browser_ver={}", os_version, browser_version))
						);
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


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UIBrowserConfigNode::UIBrowserConfigNode() {

	}
	UIBrowserConfigNode::~UIBrowserConfigNode() {

	}
	void UIBrowserConfigNode::SetTitle(const std::string& title) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("6C0B97862744"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(title).c_str());
		} while (0);
	}
	std::string UIBrowserConfigNode::GetTitle() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("6C0B97862744"));
			if (!edit)
				break;
			auto w = edit->GetText();
			if (w.IsEmpty())
				break;
			result = shared::IConv::WStringToMBytes(w.GetData());
		} while (0);
		return result;
	}

	void UIBrowserConfigNode::SetUrl(const std::string& url) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("DA3F9E9298CE"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(url).c_str());
		} while (0);
	}
	std::string UIBrowserConfigNode::GetUrl() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("DA3F9E9298CE"));
			if (!edit)
				break;
			auto w = edit->GetText();
			if (w.IsEmpty())
				break;
			result = shared::IConv::WStringToMBytes(w.GetData());
		} while (0);
		return result;
	}

	void UIBrowserConfigNode::SetUserDataPath(const std::string& path) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("F8B9E7C04300"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(path).c_str());
		} while (0);
	}
	std::string UIBrowserConfigNode::GetUserDataPath() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("F8B9E7C04300"));
			if (!edit)
				break;
			auto w = edit->GetText();
			if (w.IsEmpty())
				break;
			result = shared::IConv::WStringToMBytes(w.GetData());
		} while (0);
		return result;
	}

	void UIBrowserConfigNode::SetOSVersion(const std::string& version) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("6A72B8AC487E"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(version).c_str());
		} while (0);
	}
	std::string UIBrowserConfigNode::GetOSVersion() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("6A72B8AC487E"));
			if (!edit)
				break;
			auto w = edit->GetText();
			if (w.IsEmpty())
				break;
			result = shared::IConv::WStringToMBytes(w.GetData());
		} while (0);
		return result;
	}

	void UIBrowserConfigNode::SetBrowserVersion(const std::string& version) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("7829F0EE1CF1"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(version).c_str());
		} while (0);
	}
	std::string UIBrowserConfigNode::GetBrowserVersion() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("7829F0EE1CF1"));
			if (!edit)
				break;
			auto w = edit->GetText();
			if (w.IsEmpty())
				break;
			result = shared::IConv::WStringToMBytes(w.GetData());
		} while (0);
		return result;
	}

	UIBrowserConfigList::UIBrowserConfigList() {

	}
	UIBrowserConfigList::~UIBrowserConfigList() {

	}
	UIBrowserConfigNode* UIBrowserConfigList::AppendBrowserConfig() {
		bool result = false;
		CDialogBuilder builder;
		auto node = builder.Create<UIBrowserConfigNode>(_T("browser_config_node.xml"));


		Add(node);
		return node;
	}
	bool UIBrowserConfigList::RemoveBrowserConfig(UIBrowserConfigNode*) {
		bool result = false;



		return result;
	}





}///namespace local