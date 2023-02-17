#if !defined(__8B98E179_4E89_4B40_879E_BBF96DBFDF0B__)
#define __8B98E179_4E89_4B40_879E_BBF96DBFDF0B__

namespace local {
	const wchar_t MAIN_WINDOW_TITLE[] = L"Browser® Manager® [2023.2.10]";



	class BrowserConfigNode final {
	public:
  std::uint64_t identify = 0;
  std::string comment;
  std::string jump_url;
  std::string user_data_dir;
  std::vector<std::string> browser_version;

#if 0
  "identify":0,
   "comment" : "浏览器测试配置",
   "jump_url" : "",
   "user_data_dir" : "",
   "browser_version" : [
    "100.0.0.0",
     "100.0.0.1",
     "100.1.0.2"
   ] ,
   "os_version" : "",
     "proxy_enable" : true,
     "proxy_address" : "",
     "proxy_account" : "",
     "proxy_password" : "",
     "user_agent" : [
      "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36",
       "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36 Edg/110.0.1587.46"
     ] ,
     "dynamic_configure" : true
#endif
	};




}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 16 Feb 2023 02:02:18 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__8B98E179_4E89_4B40_879E_BBF96DBFDF0B__