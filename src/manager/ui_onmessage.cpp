#include "stdafx.h"

namespace local {
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
						rapidjson::Value().SetString(proxy_address.c_str(),doc.GetAllocator()).Move(), doc.GetAllocator());
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
}///namespace local