#include "stdafx.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
 switch (ul_reason_for_call) {
 case DLL_PROCESS_ATTACH: {
#if defined(_DEBUG)
  ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //::_CrtSetBreakAlloc(37968);
#endif
 }break;
 case DLL_THREAD_ATTACH: {
 }break;
 case DLL_THREAD_DETACH: {
 }break;
 case DLL_PROCESS_DETACH: {
#ifdef _DEBUG
  //::_CrtDumpMemoryLeaks();
#endif
 }break;
 }
 return TRUE;
}
