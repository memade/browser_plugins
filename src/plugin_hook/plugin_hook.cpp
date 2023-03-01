#include "stdafx.h"

namespace local {

 Plugin::Plugin() {
  Init();
 }

 Plugin::~Plugin() {
  UnInit();
 }

 void Plugin::Release() const {
  delete this;
 }

 void Plugin::Init() {
  m_pConfig = new Config();
 }

 void Plugin::UnInit() {
  m_pConfig->Release();
 }

 Config* Plugin::ConfigGet() const {
  return m_pConfig;
 }

 static auto defGetFontData = [](_In_ HDC hdc,
  _In_ DWORD   dwTable,
  _In_ DWORD   dwOffset,
  _Out_writes_bytes_to_opt_(cjBuffer, return) PVOID pvBuffer,
  _In_ DWORD   cjBuffer)->DWORD {
   //::MessageBoxW(NULL, L"GetFontData", NULL, NULL);
   return __gpPlugin->GetFontDataLocal(
    hdc,
    dwTable,
    dwOffset,
    pvBuffer,
    cjBuffer
   );
 };

 static auto defEnumFontFamiliesExW = [](
  _In_ HDC hdc, _In_ LPLOGFONTW lpLogfont, _In_ FONTENUMPROCW lpProc, _In_ LPARAM lParam, _In_ DWORD dwFlags)->int {
   //::MessageBoxW(NULL, L"EnumFontFamiliesExW", NULL, NULL);
   return __gpPlugin->EnumFontFamiliesExWLocal(
    hdc,
    lpLogfont,
    lpProc,
    lParam,
    dwFlags
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
   BOOL result = __gpPlugin->CreateProcessAsUserWLocal(
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
   //::MessageBoxW(NULL, lpCommandLine ? lpCommandLine : L"", NULL, NULL);
   return result;
 };

 bool Plugin::Start() {
  GetFontDataRemote = defGetFontData;
  m_DetoursDetourAttachMap.emplace(&(PVOID&)GetFontDataLocal, GetFontDataRemote);
  EnumFontFamiliesExWRemote = defEnumFontFamiliesExW;
  m_DetoursDetourAttachMap.emplace(&(PVOID&)EnumFontFamiliesExWLocal, EnumFontFamiliesExWRemote);
  CreateProcessAsUserWRemote = defCreateProcessAsUserW;
  m_DetoursDetourAttachMap.emplace(&(PVOID&)CreateProcessAsUserWLocal, CreateProcessAsUserWRemote);
  DetoursDetourAttach();
  return true;
 }

 void Plugin::Stop() {
  DetoursDetourDetach();
 }

 void Plugin::DetoursDetourAttach() const {
  shared::detours::DetourRestoreAfterWith();
  shared::detours::DetourTransactionBegin();
  shared::detours::DetourUpdateThread(::GetCurrentThread());
  for (const auto& node : m_DetoursDetourAttachMap)
   shared::detours::DetourAttach(node.first, node.second);
  shared::detours::DetourTransactionCommit();
 }
 void Plugin::DetoursDetourDetach() const {
  shared::detours::DetourTransactionBegin();
  shared::detours::DetourUpdateThread(::GetCurrentThread());
  for (const auto& node : m_DetoursDetourAttachMap)
   shared::detours::DetourDetach(node.first, node.second);
  shared::detours::DetourTransactionCommit();
 }

 Plugin* __gpPlugin = nullptr;
}///namespace local