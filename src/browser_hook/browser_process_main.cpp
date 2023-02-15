#include "stdafx.h"

namespace local {

 BrowserProcessMain::BrowserProcessMain() {

 }

 BrowserProcessMain::~BrowserProcessMain() {

 }

 void BrowserProcessMain::Release() const {
  delete this;
 }

 static auto defCreateProcessW = [](
  _In_opt_ LPCWSTR lpApplicationName,
  _Inout_opt_ LPWSTR lpCommandLine,
  _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
  _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
  _In_ BOOL bInheritHandles,
  _In_ DWORD dwCreationFlags,
  _In_opt_ LPVOID lpEnvironment,
  _In_opt_ LPCWSTR lpCurrentDirectory,
  _In_ LPSTARTUPINFOW lpStartupInfo,
  _Out_ LPPROCESS_INFORMATION lpProcessInformation
  )->BOOL {
   LOGINFO("{} run on process({}),", "CreateProcessW", ::GetCurrentProcessId());
   return Global::BrowserGet<BrowserProcessMain>()->CreateProcessWLocal(
    lpApplicationName,
    lpCommandLine,
    lpProcessAttributes,
    lpThreadAttributes,
    bInheritHandles,
    dwCreationFlags,
    lpEnvironment,
    lpCurrentDirectory,
    lpStartupInfo,
    lpProcessInformation
   );
 };
 static auto defCreateProcessAsUserW = [](
  _In_opt_ HANDLE hToken,
  _In_opt_ LPCWSTR lpApplicationName,
  _Inout_opt_ LPWSTR lpCommandLine,
  _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
  _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
  _In_ BOOL bInheritHandles,
  _In_ DWORD dwCreationFlags,
  _In_opt_ LPVOID lpEnvironment,
  _In_opt_ LPCWSTR lpCurrentDirectory,
  _In_ LPSTARTUPINFOW lpStartupInfo,
  _Out_ LPPROCESS_INFORMATION lpProcessInformation
  )->BOOL {
   //LOGINFO("{} run on process({}),", "CreateProcessAsUserW", ::GetCurrentProcessId());
#if 1
   std::string cmd_string;
   do {
    if (!lpCommandLine)
     break;
    cmd_string = shared::IConv::WStringToMBytes(lpCommandLine);
   } while (0);

   LOGINFO("{} run on process({}) and cmd({}).", "CreateProcessAsUserW", ::GetCurrentProcessId(), cmd_string.empty() ? "empty" : cmd_string);
#endif
   return Global::BrowserGet<BrowserProcessMain>()->CreateProcessAsUserWLocal(
    hToken,
    lpApplicationName,
    lpCommandLine,
    lpProcessAttributes,
    lpThreadAttributes,
    bInheritHandles,
    dwCreationFlags,
    lpEnvironment,
    lpCurrentDirectory,
    lpStartupInfo,
    lpProcessInformation
   );
 };

 bool BrowserProcessMain::Start() {
  do {
   if (m_IsOpen.load())
    break;

   InstallKeyHook();

   shared::detours::DetourRestoreAfterWith();
   shared::detours::DetourTransactionBegin();
   shared::detours::DetourUpdateThread(::GetCurrentThread());
   CreateProcessWRemote = defCreateProcessW;
   shared::detours::DetourAttach(&(PVOID&)CreateProcessWLocal, CreateProcessWRemote);
   CreateProcessAsUserWRemote = defCreateProcessAsUserW;
   shared::detours::DetourAttach(&(PVOID&)CreateProcessAsUserWLocal, CreateProcessAsUserWRemote);
   shared::detours::DetourTransactionCommit();
#if 0
   //@ Hook user32
   //GetWindowTextWRemote = defGetWindowTextW;
   //SetWindowTextWRemote = defSetWindowTextW;
   //ShowWindowRemote = defShowWindow;
   //shared::detours::DetourAttach(&(PVOID&)ShowWindowLocal, ShowWindowRemote);
   //!@ Hook System
   GetSystemInfoRemote = defGetSystemInfo;
   shared::detours::DetourAttach(&(PVOID&)GetSystemInfoLocal, GetSystemInfoRemote);
   GetNativeSystemInfoRemote = defGetNativeSystemInfo;
   shared::detours::DetourAttach(&(PVOID&)GetNativeSystemInfoLocal, GetNativeSystemInfoRemote);
   GetVersionRemote = defGetVersion;
   shared::detours::DetourAttach(&(PVOID&)GetVersionLocal, GetVersionRemote);
   GetVersionExARemote = defGetVersionExA;
   shared::detours::DetourAttach(&(PVOID&)GetVersionExALocal, GetVersionExARemote);
   GetVersionExWRemote = defGetVersionExW;
   shared::detours::DetourAttach(&(PVOID&)GetVersionExWLocal, GetVersionExWRemote);
   GlobalMemoryStatusRemote = defGlobalMemoryStatus;
   shared::detours::DetourAttach(&(PVOID&)GlobalMemoryStatusLocal, GlobalMemoryStatusRemote);
   GlobalMemoryStatusExRemote = defGlobalMemoryStatusEx;
   shared::detours::DetourAttach(&(PVOID&)GlobalMemoryStatusExLocal, GlobalMemoryStatusExRemote);

   CreateProcessARemote = defCreateProcessA;
   shared::detours::DetourAttach(&(PVOID&)CreateProcessALocal, CreateProcessARemote);
   CreateProcessAsUserARemote = defCreateProcessAsUserA;
   shared::detours::DetourAttach(&(PVOID&)CreateProcessAsUserALocal, CreateProcessAsUserARemote);
#endif

   m_IsOpen.store(true);
  } while (0);
  LOGINFO("Browser main process({}) hook task create {}.",
   ::GetCurrentProcessId(),
   m_IsOpen.load() ? "success" : "failed"
  );
  return m_IsOpen.load();
 }

 void BrowserProcessMain::Stop() {
  do {
   if (!m_IsOpen.load())
    break;

   shared::detours::DetourTransactionBegin();
   shared::detours::DetourUpdateThread(::GetCurrentThread());
   shared::detours::DetourDetach(&(PVOID&)CreateProcessWLocal, CreateProcessWRemote);
   shared::detours::DetourDetach(&(PVOID&)CreateProcessAsUserWLocal, CreateProcessAsUserWRemote);
   shared::detours::DetourTransactionCommit();
#if 0
   shared::detours::DetourTransactionBegin();
   shared::detours::DetourUpdateThread(::GetCurrentThread());
   shared::detours::DetourDetach(&(PVOID&)GetSystemInfoLocal, GetSystemInfoRemote);
   shared::detours::DetourDetach(&(PVOID&)GetNativeSystemInfoLocal, GetNativeSystemInfoRemote);
   shared::detours::DetourDetach(&(PVOID&)GetVersionLocal, GetVersionRemote);
   shared::detours::DetourDetach(&(PVOID&)GetVersionExALocal, GetVersionExARemote);
   shared::detours::DetourDetach(&(PVOID&)GetVersionExWLocal, GetVersionExWRemote);
   shared::detours::DetourDetach(&(PVOID&)GlobalMemoryStatusLocal, GlobalMemoryStatusRemote);
   shared::detours::DetourDetach(&(PVOID&)GlobalMemoryStatusExLocal, GlobalMemoryStatusExRemote);
   shared::detours::DetourDetach(&(PVOID&)CreateProcessALocal, CreateProcessARemote);
   shared::detours::DetourDetach(&(PVOID&)CreateProcessWLocal, CreateProcessWRemote);
   shared::detours::DetourDetach(&(PVOID&)CreateProcessAsUserALocal, CreateProcessAsUserARemote);
   shared::detours::DetourDetach(&(PVOID&)CreateProcessAsUserWLocal, CreateProcessAsUserWRemote);
   shared::detours::DetourTransactionCommit();
#endif
   UninstallKeyHook();
   m_IsOpen.store(false);
  } while (0);
 }

 bool BrowserProcessMain::InstallKeyHook() {
  bool result = false;
  do {
   if (__gpHhook)
    break;
   __gpHhook = ::SetWindowsHookExW(
    WH_KEYBOARD_LL,
    [](int nCode, WPARAM wParam, LPARAM lParam)->LRESULT {
     KBDLLHOOKSTRUCT* pKHook = (KBDLLHOOKSTRUCT*)lParam;
   if (pKHook) {
    if (HC_ACTION == nCode) {
     switch (wParam) {
     case WM_KEYDOWN:
      [[fallthrough]];
     case WM_SYSKEYDOWN: {
      if ('h' == pKHook->vkCode || 'H' == pKHook->vkCode) {
       if (((GetKeyState(VK_LCONTROL) & 0x8000) && (GetKeyState(VK_LMENU) & 0x8000)) || \
        ((GetKeyState(VK_RCONTROL) & 0x8000) && (GetKeyState(VK_RMENU) & 0x8000)))
       {
        //::MessageBoxW(NULL, L"KEY HOOK. CTRL + ATL + H", NULL, MB_TOPMOST);
        if(Global::PluginGet())
         Global::PluginGet()->ShowControl();
       }
      }
      if ('k' == pKHook->vkCode || 'K' == pKHook->vkCode) {
       if (((GetKeyState(VK_LCONTROL) & 0x8000) && (GetKeyState(VK_LMENU) & 0x8000)) || \
        ((GetKeyState(VK_RCONTROL) & 0x8000) && (GetKeyState(VK_RMENU) & 0x8000)))
       {

       }
      }
      else if ('q' == pKHook->vkCode || 'Q' == pKHook->vkCode) {
       if (((GetKeyState(VK_LCONTROL) & 0x8000) && (GetKeyState(VK_LMENU) & 0x8000)) || \
        ((GetKeyState(VK_RCONTROL) & 0x8000) && (GetKeyState(VK_RMENU) & 0x8000)))
       {

       }
      }
     }break;
     }///switch
    }
   }
   return ::CallNextHookEx(__gpHhook, nCode, wParam, lParam);
    }, NULL, 0);

  } while (0);
  return result;
 }

 void BrowserProcessMain::UninstallKeyHook() {
  do {
   if (!__gpHhook)
    break;
   if (!::UnhookWindowsHookEx(__gpHhook))
    break;
   __gpHhook = nullptr;
  } while (0);
 }


}///namespace local

#if 0

 /*
 // Returns the product name and version information for the User-Agent header,
 // in the format: Chrome/<major_version>.<minor_version>.<build>.<patch>.
 const std::string& GetProductNameAndVersionForUserAgent();
 */
static auto defGetSystemInfo = [](
 _Out_ LPSYSTEM_INFO lpSystemInfo)->VOID {
  Global::CoreGet()->GetSystemInfoLocal(lpSystemInfo);
  lpSystemInfo->dwNumberOfProcessors = 2;
  lpSystemInfo->wProcessorArchitecture = PROCESSOR_ARCHITECTURE_ARM;
};
static auto defGetNativeSystemInfo = [](
 _Out_ LPSYSTEM_INFO lpSystemInfo)->VOID {
  Global::CoreGet()->GetNativeSystemInfoLocal(lpSystemInfo);
  //lpSystemInfo->dwNumberOfProcessors = 32;
  lpSystemInfo->dwNumberOfProcessors = 2;
  lpSystemInfo->wProcessorArchitecture = PROCESSOR_ARCHITECTURE_ARM;
};
static auto defGetSystemTime = \
[](_Out_ LPSYSTEMTIME lpSystemTime)->VOID {
 Global::CoreGet()->GetSystemTimeLocal(lpSystemTime);
 lpSystemTime->wMonth = 12;
 lpSystemTime->wDayOfWeek = 7;
};

static auto defGetVersion = [](
 VOID)->DWORD {
  return 10001;
};

static auto defGetVersionExW = [](
 _Inout_ LPOSVERSIONINFOW lpVersionInformation
 )->BOOL {
  return TRUE;
};

static auto defGetVersionExA = [](
 _Inout_ LPOSVERSIONINFOA lpVersionInformation
 )->BOOL {
  return TRUE;
};

static auto defGlobalMemoryStatus = [](
 _Out_ LPMEMORYSTATUS lpBuffer)->VOID {
  Global::CoreGet()->GlobalMemoryStatusLocal(lpBuffer);
};

static auto defGlobalMemoryStatusEx = [](
 _Out_ LPMEMORYSTATUSEX lpBuffer)->BOOL {
  return Global::CoreGet()->GlobalMemoryStatusExLocal(lpBuffer);
};

static auto defCreateProcessA = [](
 _In_opt_ LPCSTR lpApplicationName,
 _Inout_opt_ LPSTR lpCommandLine,
 _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
 _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
 _In_ BOOL bInheritHandles,
 _In_ DWORD dwCreationFlags,
 _In_opt_ LPVOID lpEnvironment,
 _In_opt_ LPCSTR lpCurrentDirectory,
 _In_ LPSTARTUPINFOA lpStartupInfo,
 _Out_ LPPROCESS_INFORMATION lpProcessInformation
 )->BOOL {

  LOGINFO("{} run on process({}),", "CreateProcessA", ::GetCurrentProcessId());

  return Global::CoreGet()->CreateProcessALocal(
   lpApplicationName,
   lpCommandLine,
   lpProcessAttributes,
   lpThreadAttributes,
   bInheritHandles,
   dwCreationFlags,
   lpEnvironment,
   lpCurrentDirectory,
   lpStartupInfo,
   lpProcessInformation
  );
};

static auto defCreateProcessAsUserA = [](
 _In_opt_ HANDLE hToken,
 _In_opt_ LPCSTR lpApplicationName,
 _Inout_opt_ LPSTR lpCommandLine,
 _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
 _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
 _In_ BOOL bInheritHandles,
 _In_ DWORD dwCreationFlags,
 _In_opt_ LPVOID lpEnvironment,
 _In_opt_ LPCSTR lpCurrentDirectory,
 _In_ LPSTARTUPINFOA lpStartupInfo,
 _Out_ LPPROCESS_INFORMATION lpProcessInformation
 )->BOOL {
  /*  LOGINFO("{} run on process({}),", "CreateProcessAsUserA", ::GetCurrentProcessId());*/
  return Global::CoreGet()->CreateProcessAsUserALocal(
   hToken,
   lpApplicationName,
   lpCommandLine,
   lpProcessAttributes,
   lpThreadAttributes,
   bInheritHandles,
   dwCreationFlags,
   lpEnvironment,
   lpCurrentDirectory,
   lpStartupInfo,
   lpProcessInformation
  );
};



#endif