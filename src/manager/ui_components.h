#if !defined(__D1B87E74_7CDB_4540_BF01_25488D716988__)
#define __D1B87E74_7CDB_4540_BF01_25488D716988__

namespace local {

 class UICombo final : public CControlUI {
 public:
 public:
  UICombo(void) { m_hWnd = NULL; };
  ~UICombo(void) {};
  virtual void SetInternVisible(bool bVisible = true)
  {
   __super::SetInternVisible(bVisible);
   ::ShowWindow(m_hWnd, bVisible);
  }
  virtual void SetPos(RECT rc)
  {
   __super::SetPos(rc);
   ::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
  }
  BOOL Attach(HWND hWndNew)
  {
   if (!::IsWindow(hWndNew))
   {
    return FALSE;
   }
   m_hWnd = hWndNew;
   return TRUE;
  }
  HWND Detach()
  {
   HWND hWnd = m_hWnd;
   m_hWnd = NULL;
   return hWnd;
  }
 protected:
  HWND m_hWnd;
 };

 class UIBrowserConfigPage final : public CVerticalLayoutUI {
 public:
  UIBrowserConfigPage();
  virtual ~UIBrowserConfigPage();
 public:
  void SetTitle(const std::string&);
  std::string GetTitle();
  void SetJumpUrl(const std::string&);
  std::string GetJumpUrl();
  void SetBrowserVersion(const std::string&);
  std::string GetBrowserVersion();
  void SetOSVersion(const std::string&);
  std::string GetOSVersion();
  void SetUserDataPath(const std::string&);
  std::string GetUserDataPath();
  void SetProxyAddress(const std::string&);
  std::string GetProxyAddress();
  void SetProxyAccount(const std::string&);
  std::string GetProxyAccount();
  void SetProxyPassword(const std::string&);
  std::string GetProxyPassword();
 };
#if 0
 class UIBrowserConfigList final : public CListUI {
 public:
  UIBrowserConfigList();
  virtual ~UIBrowserConfigList();
 public:
  UIBrowserConfigNode* AppendBrowserConfig();
  bool RemoveBrowserConfig(UIBrowserConfigNode*);
 private:

 };
#endif


}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 16 Feb 2023 02:02:45 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__D1B87E74_7CDB_4540_BF01_25488D716988__