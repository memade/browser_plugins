#if !defined(__794468B0_0ABF_4792_8D17_7C8C2251F73E__)
#define __794468B0_0ABF_4792_8D17_7C8C2251F73E__

namespace local {

 class Plugin final : public IBrowserPlugin {
 protected:
  std::shared_ptr<std::mutex> m_Mutex = std::make_shared<std::mutex>();
 public:
  Plugin();
  virtual ~Plugin();
  void Release() const override final;
 private:
  void Init();
  void UnInit();
 protected:
  IConfig* ConfigGet() const override final;
  bool Start() override final;
  void Stop() override final;
  void EnumPluginPath(const char* folder_path, const std::function<void(const char*)>&) override final;
 private:
  Config* m_pConfig = nullptr;
 };

 extern Plugin* __gpPlugin;
}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 24 Feb 2023 15:27:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__794468B0_0ABF_4792_8D17_7C8C2251F73E__
