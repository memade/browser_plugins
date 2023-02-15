#if !defined(__3166F42B_6A3E_4FF4_BF12_F20EE19F1154__)
#define __3166F42B_6A3E_4FF4_BF12_F20EE19F1154__

namespace local {

 class ChromiumPlugin
  : public shared::hook::Kernel32
  , public shared::hook::System {
 public:
  ChromiumPlugin();
  virtual ~ChromiumPlugin();
 public:
  Config* ConfigGet() const;
  bool Start();
  void Stop();
  const EnBrowserProcessType& BrowserProcessType() const;
 private:
  void Init();
  void UnInit();
 protected:
  EnBrowserProcessType m_ProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_UNKNOWN;
  Config* m_pConfig = nullptr;
  std::atomic_bool m_IsOpen = false;
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 private:
  void DetoursDetourAttach() const;
  void DetoursDetourDetach() const;
  std::map<void**, void*> m_DetoursDetourAttachMap;
 };

}///namespace local


/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 13 Feb 2023 01:48:42 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__3166F42B_6A3E_4FF4_BF12_F20EE19F1154__


