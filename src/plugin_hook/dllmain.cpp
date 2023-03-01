#include "stdafx.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	BOOL result = TRUE;
	do {
		if (shared::detours::DetourIsHelperProcess())
			break;
		switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH: {
#if defined(_DEBUG)
			::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			//::_CrtSetBreakAlloc(9515);
#endif
		}break;
		case DLL_THREAD_ATTACH: {
		}break;
		case DLL_THREAD_DETACH: {
		}break;
		case DLL_PROCESS_DETACH: {
		}break;
		}
	} while (0);
	return result;
}
