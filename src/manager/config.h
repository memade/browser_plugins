#if !defined(__46A8E394_4F3F_4A0F_B393_B8F445D63E8D__)
#define __46A8E394_4F3F_4A0F_B393_B8F445D63E8D__

namespace local {
	

	class Config final {
		std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
	public:
		Config();
		~Config();
	public:
		void Init();
		void UnInit();
 public:
		std::vector<std::string> UserBrowserConfigsSnapshoot() const;
  bool PushUserBrowserConfig(const std::string& json_node);
  void PopUserBrowserConfig(const std::uint64_t&);
		std::string GetUserBrowserConfig(const std::uint64_t&) const;
		bool UserBrowserConfigEmpty() const;
	private:
  shared::container::map<std::uint64_t, std::string> m_UserBrowserConfigDatas;
		std::string m_UserBrowserConfigPathname;
		std::vector<std::thread> m_Threads;
		std::atomic_bool m_IsOpen = false;
		void Process();
		std::atomic_bool m_NotifyFlag = false;
		std::uint64_t m_ConfigureCacheIntervalMS = 3000;
	};



}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 17 Feb 2023 08:11:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__46A8E394_4F3F_4A0F_B393_B8F445D63E8D__
