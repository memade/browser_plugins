#if !defined(__8AC244AE_620A_47C4_94F6_0A67C833EAB5__)
#define __8AC244AE_620A_47C4_94F6_0A67C833EAB5__

namespace local {


#if 0
 class BrowserProcessMain : public ChromiumPlugin, public shared::hook::Kernel32 {
 public:
  BrowserProcessMain();
 public:
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;
 private:
  bool InstallKeyHook();
  void UninstallKeyHook();
  virtual ~BrowserProcessMain();
 };

 class BrowserProcessGpu : public IBrowser {
 public:
  BrowserProcessGpu();
 public:
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;
 protected:
  virtual ~BrowserProcessGpu();
 };

 class BrowserProcessRenderer : public IBrowser , public shared::hook::User32 {
 public:
  BrowserProcessRenderer();
 public:
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;
 protected:
  virtual ~BrowserProcessRenderer();
 };

 class BrowserProcessUtility : public IBrowser {
 public:
  BrowserProcessUtility();
 public:
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;
 protected:
  virtual ~BrowserProcessUtility();
 };

 class BrowserProcessCrashpadHandler : public IBrowser {
 public:
  BrowserProcessCrashpadHandler();
 public:
  bool Start() override final;
  void Stop() override final;
  void Release() const override final;
 protected:
  virtual ~BrowserProcessCrashpadHandler();
 };
#endif
}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 11 Feb 2023 08:51:48 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__8AC244AE_620A_47C4_94F6_0A67C833EAB5__

