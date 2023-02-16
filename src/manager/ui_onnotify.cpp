#include "stdafx.h"

namespace local {

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
			if (!name.Compare(_T("0CD60B5CCD92"))) {
				::ShowWindow(m_hWnd, SW_SHOWMINIMIZED);
			}
			else if (!name.Compare(_T("CECFE7E922C5"))) {//!@ 程序关闭退出
				if (IDYES == ::MessageBoxW(m_hWnd, L"Whether to exit the program?", MAIN_WINDOW_TITLE, MB_YESNO))
					__super::Close();
			}
			else if (!name.Compare(_T("386B30157DA4"))) {//!@ 启动浏览器
				OnBtnStartupBrowser(msg.pSender);
			}
			else if (!name.Compare(_T("7D0C8FBC3E87"))) {//!@ 保存(修改、添加)浏览器配置
				OnBtnSaveBrowserConfig(msg.pSender);
			}
			else if (!name.Compare(_T("4EDCE540D108"))) {//!@ 移除(删除)浏览器配置
				OnBtnRemoveBrowserConfig(msg.pSender);
			}
			else if (!name.Compare(_T("D7D2C2351734"))) {//!@ 创建、添加浏览器配置
				OnBtnAppendBrowserConfig(msg.pSender);
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

}///namespace local