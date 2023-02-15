#include "stdafx.h"

#if 0
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
 local::__gpHinstance = hModule;
 switch (ul_reason_for_call) {
 case DLL_PROCESS_ATTACH: {
#if defined(_DEBUG)
  ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//::_CrtSetBreakAlloc(37968);
#endif
  do {
   if (local::__gpOriginModule)
    break;
   std::string chrome_elf_origin_pathname = shared::Win::GetModulePathA() + "chrome_elf_origin.dll";
   local::__gpOriginModule = ::LoadLibraryA(chrome_elf_origin_pathname.c_str());
   if (!local::__gpOriginModule)
    break;
   local::__gpGlobal = new local::Global();
  } while (0);
 }break;
 case DLL_THREAD_ATTACH: {
 }break;
 case DLL_THREAD_DETACH: {
 }break;
 case DLL_PROCESS_DETACH: {
  SK_FREE_LIBRARY(local::__gpOriginModule);
  SK_DELETE_PTR(local::__gpGlobal);
#ifdef _DEBUG
  //::_CrtDumpMemoryLeaks();
#endif
 }break;
 }
 return TRUE;
}
#endif

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
 if (fdwReason != DLL_PROCESS_ATTACH)
  return TRUE;

 //::MessageBoxW(NULL, L"Hijack begin.", NULL, MB_TOPMOST);
 std::string chrome_elf_origin_pathname = shared::Win::GetModulePathA() + "chrome_elf_origin.dll";
 HMODULE real_dll = ::LoadLibraryA(chrome_elf_origin_pathname.c_str());
 if (shared::hijack::monoxgas::RebuildExportTable((PBYTE)hinstDLL, (PBYTE)real_dll))
  ::MessageBoxW(NULL, L"Hijack success.", NULL, MB_TOPMOST);

 return (TRUE);
}
