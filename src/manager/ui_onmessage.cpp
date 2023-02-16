#include "stdafx.h"

namespace local {
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
 void Manager::OnBtnAppendBrowserConfig(CControlUI* pSender) {

 }
 void Manager::OnBtnRemoveBrowserConfig(CControlUI* pSender) {

 }
 void Manager::OnBtnSaveBrowserConfig(CControlUI* pSender) {

 }
}///namespace local