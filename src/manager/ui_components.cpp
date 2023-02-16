#include "stdafx.h"

namespace local {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UIBrowserConfigPage::UIBrowserConfigPage() {

	}
	UIBrowserConfigPage::~UIBrowserConfigPage() {

	}
	void UIBrowserConfigPage::SetTitle(const std::string& title) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("6C0B97862744"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(title).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetTitle() {
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

	void UIBrowserConfigPage::SetJumpUrl(const std::string& url) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("DA3F9E9298CE"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(url).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetJumpUrl() {
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

	void UIBrowserConfigPage::SetUserDataPath(const std::string& path) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("F8B9E7C04300"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(path).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetUserDataPath() {
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

	void UIBrowserConfigPage::SetOSVersion(const std::string& version) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("6A72B8AC487E"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(version).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetOSVersion() {
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

	void UIBrowserConfigPage::SetBrowserVersion(const std::string& version) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("7829F0EE1CF1"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(version).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetBrowserVersion() {
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

	void UIBrowserConfigPage::SetProxyAddress(const std::string& address) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("5DFAF388FD1F"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(address).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetProxyAddress() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("5DFAF388FD1F"));
			if (!edit)
				break;
			auto w = edit->GetText();
			if (w.IsEmpty())
				break;
			result = shared::IConv::WStringToMBytes(w.GetData());
		} while (0);
		return result;
	}
	void UIBrowserConfigPage::SetProxyAccount(const std::string& account) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("0C9DAC6E6D51"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(account).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetProxyAccount() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("0C9DAC6E6D51"));
			if (!edit)
				break;
			auto w = edit->GetText();
			if (w.IsEmpty())
				break;
			result = shared::IConv::WStringToMBytes(w.GetData());
		} while (0);
		return result;
	}
	void UIBrowserConfigPage::SetProxyPassword(const std::string& password) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("4E120C0F957B"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(password).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetProxyPassword() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("4E120C0F957B"));
			if (!edit)
				break;
			auto w = edit->GetText();
			if (w.IsEmpty())
				break;
			result = shared::IConv::WStringToMBytes(w.GetData());
	} while (0);
	return result;
	}
#if 0
	UIBrowserConfigList::UIBrowserConfigList() {

	}
	UIBrowserConfigList::~UIBrowserConfigList() {

	}
	UIBrowserConfigPage* UIBrowserConfigList::AppendBrowserConfig() {
		bool result = false;
		CDialogBuilder builder;
		auto node = builder.Create<UIBrowserConfigPage>(_T("browser_config_list_action_node.xml"));


		Add(node);
		return node;
	}
	bool UIBrowserConfigList::RemoveBrowserConfig(UIBrowserConfigPage*) {
		bool result = false;



		return result;
	}

#endif





}///namespace local