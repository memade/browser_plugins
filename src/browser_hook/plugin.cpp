#include "stdafx.h"

namespace local {
 ChromiumPlugin::ChromiumPlugin() {
  Init();
 }
 ChromiumPlugin::~ChromiumPlugin() {
  UnInit();
 }
 void ChromiumPlugin::Init() {

 }

 void ChromiumPlugin::UnInit() {

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
   return Global::PluginGet()->CreateProcessWLocal(
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
   BOOL result = Global::PluginGet()->CreateProcessAsUserWLocal(
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
#if 0
   do {
    if (!lpProcessInformation)
     break;
    std::string resDll = shared::Win::Resource::Load(__gpHinstance, IDR_INJECTOR_DLL, "RES");
    if (resDll.empty())
     break;
    std::string shellcode;
    shared::injection::Reflecive::GenerateShellcode(resDll, "api_object_init", "", shared::injection::EnShellCodeFlag::EN_SC_CLEARHEADER, shellcode);
    if (shellcode.empty())
     break;
    if (!shared::Win::ShellcodeExecute(lpProcessInformation->hProcess, shellcode))
     break;
   } while (0);
#endif
   return result;
 };

 static auto defGetNativeSystemInfo = [](
  _Out_ LPSYSTEM_INFO lpSystemInfo)->VOID {
   Global::PluginGet()->GetNativeSystemInfoLocal(lpSystemInfo);
 };

 static auto defGetSystemInfo = [](
  _Out_ LPSYSTEM_INFO lpSystemInfo)->VOID {
   Global::PluginGet()->GetSystemInfoLocal(lpSystemInfo);
 };

 static auto defGetProductInfo = [](
  _In_ DWORD dwOSMajorVersion,
  _In_ DWORD dwOSMinorVersion,
  _In_ DWORD dwSpMajorVersion,
  _In_ DWORD dwSpMinorVersion,
  _Out_ PDWORD pdwReturnedProductType)->BOOL {
   return Global::PluginGet()->GetProductInfoLocal(dwOSMajorVersion, dwOSMinorVersion, dwSpMajorVersion, dwSpMinorVersion, pdwReturnedProductType);
 };

 static auto defGetVersion = [](
  )->DWORD {
   return Global::PluginGet()->GetVersionLocal();
 };
 static auto defGetVersionExW = [](
  _Inout_ LPOSVERSIONINFOW lpVersionInformation
  )->BOOL {
   return Global::PluginGet()->GetVersionExWLocal(lpVersionInformation);
 };

 static auto defGetVersionExA = [](
  _Inout_ LPOSVERSIONINFOA lpVersionInformation
  )->BOOL {
   return Global::PluginGet()->GetVersionExALocal(lpVersionInformation);
 };

 static auto defEnumFontFamiliesExW = [](
  _In_ HDC hdc, _In_ LPLOGFONTW lpLogfont, _In_ FONTENUMPROCW lpProc, _In_ LPARAM lParam, _In_ DWORD dwFlags)->int {
   return Global::PluginGet()->EnumFontFamiliesExWLocal(
    hdc,
    lpLogfont,
    lpProc,
    lParam,
    dwFlags
   );
 };

 static auto defGetFontData = [](_In_ HDC hdc,
  _In_ DWORD   dwTable,
  _In_ DWORD   dwOffset,
  _Out_writes_bytes_to_opt_(cjBuffer, return) PVOID pvBuffer,
  _In_ DWORD   cjBuffer)->DWORD {
   return Global::PluginGet()->GetFontDataLocal(
    hdc,
    dwTable,
    dwOffset,
    pvBuffer,
    cjBuffer
   );
 };

 static auto defGetSystemMetrics = [](
  _In_ int nIndex)->int {
   return Global::PluginGet()->GetSystemMetricsLocal(nIndex);
 };


 static auto defEnumDisplaySettingsA = [](
  _In_opt_ LPCSTR lpszDeviceName,
  _In_ DWORD iModeNum,
  _Inout_ DEVMODEA* lpDevMode)->int {
   return Global::PluginGet()->EnumDisplaySettingsALocal(lpszDeviceName, iModeNum, lpDevMode);
 };
 static auto defEnumDisplaySettingsW = [](
  _In_opt_ LPCWSTR lpszDeviceName,
  _In_ DWORD iModeNum,
  _Inout_ DEVMODEW* lpDevMode)->BOOL {
   return Global::PluginGet()->EnumDisplaySettingsWLocal(lpszDeviceName, iModeNum, lpDevMode);
 };


 static auto defGetDeviceCaps = [](
  _In_opt_ HDC hdc, _In_ int index)->int {
   return Global::PluginGet()->GetDeviceCapsLocal(hdc, index);
 };

 bool ChromiumPlugin::Start() {
  do {
   if (m_IsOpen.load())
    break;
   switch (Global::BrowserProcessTypeGet()) {
   case EnBrowserProcessType::EN_PROCESS_TYPE_MAIN: {

   }break;
   case EnBrowserProcessType::EN_PROCESS_TYPE_GPU: {
   } break;
   case EnBrowserProcessType::EN_PROCESS_TYPE_RENDERER: {
   }break;
   case EnBrowserProcessType::EN_PROCESS_TYPE_UTILITY: {
   }break;
   case EnBrowserProcessType::EN_PROCESS_TYPE_CRASHPAD: {
   }break;
   default: {

   }break;
   }

   CreateProcessWRemote = defCreateProcessW;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)CreateProcessWLocal, CreateProcessWRemote);
   CreateProcessAsUserWRemote = defCreateProcessAsUserW;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)CreateProcessAsUserWLocal, CreateProcessAsUserWRemote);

   EnumDisplaySettingsARemote = defEnumDisplaySettingsA;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)EnumDisplaySettingsALocal, EnumDisplaySettingsARemote);
   EnumDisplaySettingsWRemote = defEnumDisplaySettingsW;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)EnumDisplaySettingsWLocal, EnumDisplaySettingsWRemote);

   GetDeviceCapsRemote = defGetDeviceCaps;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)GetDeviceCapsLocal, GetDeviceCapsRemote);

   GetSystemMetricsRemote = defGetSystemMetrics;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)GetSystemMetricsLocal, GetSystemMetricsRemote);
   GetVersionRemote = defGetVersion;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)GetVersionLocal, GetVersionRemote);
   GetVersionExARemote = defGetVersionExA;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)GetVersionExALocal, GetVersionExARemote);
   GetVersionExWRemote = defGetVersionExW;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)GetVersionExWLocal, GetVersionExWRemote);
   GetSystemInfoRemote = defGetSystemInfo;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)GetSystemInfoLocal, GetSystemInfoRemote);
   GetNativeSystemInfoRemote = defGetNativeSystemInfo;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)GetNativeSystemInfoLocal, GetNativeSystemInfoRemote);
   GetProductInfoRemote = defGetProductInfo;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)GetProductInfoLocal, GetProductInfoRemote);
   GetFontDataRemote = defGetFontData;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)GetFontDataLocal, GetFontDataRemote);
   EnumFontFamiliesExWRemote = defEnumFontFamiliesExW;
   m_DetoursDetourAttachMap.emplace(&(PVOID&)EnumFontFamiliesExWLocal, EnumFontFamiliesExWRemote);
   DetoursDetourAttach();
   m_IsOpen.store(true);
  } while (0);
  return m_IsOpen.load();
 }

 void ChromiumPlugin::Stop() {
  do {
   if (!m_IsOpen.load())
    break;
   DetoursDetourDetach();
   m_IsOpen.store(false);
  } while (0);
 }


 ///////////////////////////////////////////////////////////////////////////////////////////////
 //!@ Private method
 void ChromiumPlugin::DetoursDetourAttach() const {
  shared::detours::DetourRestoreAfterWith();
  shared::detours::DetourTransactionBegin();
  shared::detours::DetourUpdateThread(::GetCurrentThread());
  for (const auto& node : m_DetoursDetourAttachMap)
   shared::detours::DetourAttach(node.first, node.second);
  shared::detours::DetourTransactionCommit();
 }
 void ChromiumPlugin::DetoursDetourDetach() const {
  shared::detours::DetourTransactionBegin();
  shared::detours::DetourUpdateThread(::GetCurrentThread());
  for (const auto& node : m_DetoursDetourAttachMap)
   shared::detours::DetourDetach(node.first, node.second);
  shared::detours::DetourTransactionCommit();
 }

}///namespace local
