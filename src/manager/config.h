#if !defined(__46A8E394_4F3F_4A0F_B393_B8F445D63E8D__)
#define __46A8E394_4F3F_4A0F_B393_B8F445D63E8D__

namespace local {
	/*
 * 
{
    "BrowserConfigPage":[
        {
            "identify":0,
            "comment":"浏览器测试配置",
            "jump_url":"",
            "user_data_dir":"",
            "browser_version":[
                "100.0.0.0",
                "100.0.0.1",
                "100.1.0.2"
            ],
            "os_version":"",
            "proxy_enable":true,
            "proxy_address":"",
            "proxy_account":"",
            "proxy_password":"",
            "user_agent":[
                "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36",
                "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36 Edg/110.0.1587.46"
            ],
            "dynamic_configure":true
        },
        {
            "identify":1,
            "comment":"浏览器测试配置",
            "jump_url":"",
            "user_data_dir":"",
            "browser_version":[
                "100.0.0.0",
                "100.0.0.1",
                "100.1.0.2"
            ],
            "os_version":"",
            "proxy_enable":true,
            "proxy_address":"",
            "proxy_account":"",
            "proxy_password":"",
            "user_agent":[
                "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36",
                "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36 Edg/110.0.1587.46"
            ],
            "dynamic_configure":true
        }
    ]
}
	
	*/



	class Config final {
		std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
	public:
		Config();
		~Config();
	private:
		void Init();
		void UnInit();
 public:
  bool AppendBrowserConfig(const std::string& json_node);
  void RemoveBrowserConfig(const std::uint64_t&);
	private:
  std::map<std::uint64_t, std::string> m_BrowserConfigs;
		std::string m_ConfigBuffer;
		std::string m_ConfigFilePathname;
		std::vector<std::thread> m_Threads;
		std::atomic_bool m_IsOpen = false;
		void Process();
	};



}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 17 Feb 2023 08:11:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__46A8E394_4F3F_4A0F_B393_B8F445D63E8D__
