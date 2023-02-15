#include "stdafx.h"

namespace local {

 BrowserProcessRenderer::BrowserProcessRenderer() {

 }

 BrowserProcessRenderer::~BrowserProcessRenderer() {

 }

 void BrowserProcessRenderer::Release() const {
  delete this;
 }

 static auto defGetWindowTextW = [](
  _In_ HWND hWnd,
  _Out_writes_(nMaxCount) LPWSTR lpString,
  _In_ int nMaxCount
  )->int {

#if 0
   int result = Global::CoreGet()->BrowserGet<BrowserProcessRenderer>()->\
    GetWindowTextWLocal(hWnd, lpString, nMaxCount);
   if (result > 0) {
    std::wstring text(lpString, result);
    LOGINFO("GetWindowTextW text({}) on process({}).", shared::IConv::WStringToMBytes(text), GetCurrentProcessId());
   }
   return result;
#endif
   return 0;
 };

 static auto defSetWindowTextW = [](
  _In_ HWND hWnd,
  _In_opt_ LPCWSTR lpString
  )->BOOL {
#if 0
   if (lpString) {
    std::string text = shared::IConv::WStringToMBytes(lpString);
    LOGINFO("SetWindowTextW text({}) on process({}).", text, GetCurrentProcessId());
   }
   return Global::CoreGet()->BrowserGet<BrowserProcessRenderer>()->\
    SetWindowTextWLocal(hWnd, lpString);
#endif
   return FALSE;
 };

 bool BrowserProcessRenderer::Start() {
  do {
   if (m_IsOpen.load())
    break;
   shared::detours::DetourRestoreAfterWith();
   shared::detours::DetourTransactionBegin();
   shared::detours::DetourUpdateThread(::GetCurrentThread());
   GetWindowTextWRemote = defGetWindowTextW;
   shared::detours::DetourAttach(&(PVOID&)GetWindowTextWLocal, GetWindowTextWRemote);
   SetWindowTextWRemote = defSetWindowTextW;
   shared::detours::DetourAttach(&(PVOID&)SetWindowTextWLocal, SetWindowTextWRemote);
   shared::detours::DetourTransactionCommit();
   m_IsOpen.store(true);
  } while (0);
  LOGINFO("Browser renderer process({}) hook task create {}.",
   ::GetCurrentProcessId(),
   m_IsOpen.load() ? "success" : "failed"
  );
  return m_IsOpen.load();
 }

 void BrowserProcessRenderer::Stop() {
  do {
   if (!m_IsOpen.load())
    break;

   shared::detours::DetourTransactionBegin();
   shared::detours::DetourUpdateThread(::GetCurrentThread());
   shared::detours::DetourDetach(&(PVOID&)GetWindowTextWLocal, GetWindowTextWRemote);
   shared::detours::DetourDetach(&(PVOID&)SetWindowTextWLocal, SetWindowTextWRemote);
   shared::detours::DetourTransactionCommit();

   m_IsOpen.store(false);
  } while (0);
 }

}///namespace local 