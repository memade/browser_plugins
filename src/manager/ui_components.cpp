#include "stdafx.h"

namespace local {











#if 0
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UIBrowserConfigPage::UIBrowserConfigPage() {

	}
	UIBrowserConfigPage::~UIBrowserConfigPage() {

	}
	UIBrowserConfigPage* UIBrowserConfigPage::Create() {
		CDialogBuilder builder;
		auto create = (UIBrowserConfigPage*)(builder.Create<UIBrowserConfigPage>(_T("browser_config_page.xml")));
		create->SetTagUINT64(shared::Win::Time::TimeStamp<std::chrono::microseconds>());
		return create;
	}
	void UIBrowserConfigPage::operator>>(std::string& output) {
		output.clear();
		rapidjson::Document doc(rapidjson::kObjectType);

		doc.AddMember(
			rapidjson::Value().SetString("identify",doc.GetAllocator()).Move(),
			rapidjson::Value().SetUint64(GetTagUINT64()).Move(), 
			doc.GetAllocator());

		doc.AddMember(
			rapidjson::Value().SetString("comment", doc.GetAllocator()).Move(),
			rapidjson::Value().SetString(GetComment().c_str(), doc.GetAllocator()).Move(),
			doc.GetAllocator());

		doc.AddMember(
			rapidjson::Value().SetString("jump_url", doc.GetAllocator()).Move(),
			rapidjson::Value().SetString(GetJumpUrl().c_str(), doc.GetAllocator()).Move(),
			doc.GetAllocator());

		doc.AddMember(
			rapidjson::Value().SetString("user_data_dir", doc.GetAllocator()).Move(),
			rapidjson::Value().SetString(GetUserDataPath().c_str(), doc.GetAllocator()).Move(),
			doc.GetAllocator());

		doc.AddMember(
			rapidjson::Value().SetString("os_version", doc.GetAllocator()).Move(),
			rapidjson::Value().SetString(GetOSVersion().c_str(), doc.GetAllocator()).Move(),
			doc.GetAllocator());

		doc.AddMember(
			rapidjson::Value().SetString("browser_version", doc.GetAllocator()).Move(),
			rapidjson::Value().SetString(GetBrowserVersion().c_str(), doc.GetAllocator()).Move(),
			doc.GetAllocator());

		doc.AddMember(
			rapidjson::Value().SetString("proxy_address", doc.GetAllocator()).Move(),
			rapidjson::Value().SetString(GetProxyAddress().c_str(), doc.GetAllocator()).Move(),
			doc.GetAllocator());

		doc.AddMember(
			rapidjson::Value().SetString("proxy_account", doc.GetAllocator()).Move(),
			rapidjson::Value().SetString(GetProxyAccount().c_str(), doc.GetAllocator()).Move(),
			doc.GetAllocator());

		doc.AddMember(
			rapidjson::Value().SetString("proxy_password", doc.GetAllocator()).Move(),
			rapidjson::Value().SetString(GetProxyPassword().c_str(), doc.GetAllocator()).Move(),
			doc.GetAllocator());

		doc.AddMember(
			rapidjson::Value().SetString("proxy_enable", doc.GetAllocator()).Move(),
			rapidjson::Value().SetBool(GetProxyEnable()).Move(),
			doc.GetAllocator());

		output = shared::Json::toString(doc);
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
	void UIBrowserConfigPage::SetName(const std::string& name) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("630565C3702C"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(name).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetName() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("630565C3702C"));
			if (!edit)
				break;
			auto w = edit->GetText();
			if (w.IsEmpty())
				break;
			result = shared::IConv::WStringToMBytes(w.GetData());
		} while (0);
		return result;
	}
	void UIBrowserConfigPage::SetComment(const std::string& title) {
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("FAD0355F8CAB"));
			if (!edit)
				break;
			edit->SetText(shared::IConv::MBytesToWString(title).c_str());
		} while (0);
	}
	std::string UIBrowserConfigPage::GetComment() {
		std::string result;
		do {
			auto edit = GetSubCtrl<CEditUI>(_T("FAD0355F8CAB"));
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
	void UIBrowserConfigPage::SetProxyEnable(const bool& enable) {
		do {
			auto check = GetSubCtrl<CCheckBoxUI>(_T("B288520F85B6"));
			if (!check)
				break;
			check->Selected(enable);
		} while (0);
	}
	bool UIBrowserConfigPage::GetProxyEnable() {
		bool result = false;
		do {
			auto check = GetSubCtrl<CCheckBoxUI>(_T("B288520F85B6"));
			if (!check)
				break;
			result = check->IsSelected();
		} while (0);
		return result;
	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////

	UIBrowserConfigListNode::UIBrowserConfigListNode() {

	}

	UIBrowserConfigListNode::~UIBrowserConfigListNode() {

	}
	UIBrowserConfigListNode* UIBrowserConfigListNode::Create() {
			CDialogBuilder builder;
			return (UIBrowserConfigListNode*)(builder.Create<UIBrowserConfigPage>(_T("browser_config_list_action_node.xml")));
	}
	void UIBrowserConfigListNode::SetTitle(const std::string& title_text) {
		auto ui = GetSubCtrl<CLabelUI>(L"9EFE15567B45");
		if (ui)
			ui->SetText(shared::IConv::MBytesToWString(title_text).c_str());
	}
	std::string UIBrowserConfigListNode::GetTitle() {
		std::string result;
		auto ui = GetSubCtrl<CLabelUI>(L"9EFE15567B45");
		if (ui)
			result = shared::IConv::WStringToMBytes(ui->GetText().GetData());
		return result;
	}



	UIBrowserConfigList::UIBrowserConfigList() {

	}
	UIBrowserConfigList::~UIBrowserConfigList() {

	}
	//UIBrowserConfigPage* UIBrowserConfigList::AppendBrowserConfig() {
	//	bool result = false;
	//	CDialogBuilder builder;
	//	auto node = builder.Create<UIBrowserConfigPage>(_T("browser_config_list_action_node.xml"));


	//	Add(node);
	//	return node;
	//}
	//bool UIBrowserConfigList::RemoveBrowserConfig(UIBrowserConfigPage*) {
	//	bool result = false;



	//	return result;
	//}






#endif
}///namespace local