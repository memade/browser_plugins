#if !defined(INC_H___678A0044_FB78_4405_A411_96F3AF4D8DA4__HEAD__)
#define INC_H___678A0044_FB78_4405_A411_96F3AF4D8DA4__HEAD__

namespace local {

	class Manager final : shared::ui::UIFrame {
	public:
		Manager();
		virtual ~Manager();
	public:
		bool Start();
		void Stop();
	private:
		void OnBtnStartupBrowser(CControlUI*);
		void OnBtnAppendBrowserConfig(CControlUI*);
		void OnBtnRemoveBrowserConfig(CControlUI*);
		void OnBtnSaveBrowserConfig(CControlUI*);
	private:
		UICombo* m_pUIComboUserAgent = nullptr;
		CControlUI* m_pComboParent = nullptr;
		CLabelUI* m_pMainWindowTitleUI = nullptr;
		CTreeViewUI* m_pUITreeViewMain = nullptr;
		CTabLayoutUI* m_pUITablayoutMain = nullptr;
		//UIBrowserConfigList* m_pUIListBrowserConfig = nullptr;
		std::atomic_bool m_IsOpen = false;
	protected:
		void CreateTray(PNOTIFYICONDATAW) override final;
		void DestoryTray(PNOTIFYICONDATAW) override final;
		void InitWindow() override final;
		void Notify(TNotifyUI& msg) override final;
		void OnFinalMessage(HWND hWnd) override final;
		CControlUI* CreateControl(LPCTSTR pstrClassName) override final;
		LPCTSTR GetWindowClassName() const override final { return _TEXT("main"); }
		LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
		LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override final;
	};



}///namespace local

/// /*新生®（上海）**/
/// /*2022_11_14T00:31:22.5133276Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___678A0044_FB78_4405_A411_96F3AF4D8DA4__HEAD__

