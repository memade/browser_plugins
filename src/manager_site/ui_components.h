#if !defined(__D1B87E74_7CDB_4540_BF01_25488D716988__)
#define __D1B87E74_7CDB_4540_BF01_25488D716988__

namespace local {

 class UIUserBrowserConfigPage;

 class UIUserBrowserConfigListItem : public ui::ListContainerElement {
 public:
  UIUserBrowserConfigListItem(const std::uint64_t&);
  UIUserBrowserConfigListItem(const std::string&);
  virtual ~UIUserBrowserConfigListItem();
  void operator>>(std::string&) const;
  void operator>>(UIUserBrowserConfigPage*) const;
  bool operator<<(const std::string&);
 public:
  const std::uint64_t& Identify() const;
  void SetTitle(const std::wstring&);
  std::wstring GetTitle();
  void UpdateTitle();
 private:
  std::uint64_t identify = 0;
  std::string name;
  std::string comment;
  std::string proxy_address;
  std::string proxy_account;
  std::string proxy_password;
  std::string user_agent;
  bool proxy_enable = false;
 private:
  std::string RawData;
  std::wstring Title;
 };

 class UIUserBrowserConfigPage : public ui::Box {
 public:
  UIUserBrowserConfigPage();
  virtual ~UIUserBrowserConfigPage();
 private:
  void Default();
 public:
  void SetTitle(const std::wstring&);
  std::wstring GetTitle();
  void SetIdentify(const std::uint64_t&);
  std::uint64_t GetIdentify();
  void SetName(const std::wstring&);
  std::wstring GetName();
  void SetComment(const std::wstring&);
  std::wstring GetComment();
  void SetUserAgent(const std::wstring&);
  void SetUserAgentDefault();
  std::wstring GetUserAgent();
  void SetProxyEnable(const bool&);
  bool GetProxyEnable();
  void ProxyCtrlEnable(const bool&);
  void SetProxyAddress(const std::wstring&);
  std::wstring GetProxyAddress();
  void SetProxyAccount(const std::wstring&);
  std::wstring GetProxyAccount();
  void SetProxyPassword(const std::wstring&);
  std::wstring GetProxyPassword();
  void SetScreenResolution(const size_t&);
  size_t GetScreenResolution();
  void SetAvailableScreenSize(const size_t&);
  size_t GetAvailableScreenSize();
  void SetHardwareConcurency(const size_t&);
  size_t GetHardwareConcurency();
  void SetPlatform(const std::wstring&);
  std::wstring GetPlatform();
  void SetWebGLUnmaskedVendor(const std::wstring&);
  std::wstring GetWebGLUnmaskedVendor();
  void SetWebGLUnmaskedRenderer(const std::wstring&);
  std::wstring GetWebGLUnmaskedRenderer();
  void SetWebGLVersion(const std::wstring&);
  std::wstring GetWebGLVersion();
  void SetJumpUrl(const std::wstring&);
  std::wstring GetJumpUrl();

  bool operator<<(const std::string&);
  bool operator<<(UIUserBrowserConfigListItem*);
  void GenerateDefaultConfig(std::string&, const std::uint64_t& identify = 0);
  std::string OutputConfig(const std::uint64_t&);
 };

 class UIUserBrowserConfigListbox : public ui::ListBox {
 public:
  UIUserBrowserConfigListbox();
  virtual ~UIUserBrowserConfigListbox();
 public:
  bool RemoveUserBrowserConfigItem();
  bool CreateUserBrowserConfigItem(const std::string&);
 };


#if 0
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
  static UIBrowserConfigPage* Create();
  void operator>>(std::string&);
 public:
  void SetTitle(const std::string&);
  std::string GetTitle();
  void SetName(const std::string&);
  std::string GetName();
  void SetComment(const std::string&);
  std::string GetComment();
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
  void SetProxyEnable(const bool&);
  bool GetProxyEnable();
 };


 class UIBrowserConfigListNode final : public CListContainerElementUI {
 public:
  UIBrowserConfigListNode();
  virtual ~UIBrowserConfigListNode();
  static UIBrowserConfigListNode* Create();
 public:
  void SetTitle(const std::string&);
  std::string GetTitle();
 };

 class UIBrowserConfigList final : public CListUI {
 public:
  UIBrowserConfigList();
  virtual ~UIBrowserConfigList();
 public:
  //UIBrowserConfigNode* AppendBrowserConfig();
  //bool RemoveBrowserConfig(UIBrowserConfigNode*);
 private:

 };
#endif
}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 16 Feb 2023 02:02:45 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__D1B87E74_7CDB_4540_BF01_25488D716988__