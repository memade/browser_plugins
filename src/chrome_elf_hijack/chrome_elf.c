#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <processthreadsapi.h>
#include <memoryapi.h>
#include <tchar.h>
#include <io.h>
#if 0
#pragma data_seg( " DLLSharedSection " )       //  声明共享数据段，并命名该数据段
int  SharedData = 0;        //  必须在定义的同时进行初始化!!!!
#pragma data_seg()
#endif

typedef void*(__stdcall* tf_api_object_init)(void*, unsigned long);
typedef void(__stdcall* tf_api_object_uninit)(void);
HMODULE hModule = NULL;
 tf_api_object_init api_object_init = NULL;
 tf_api_object_uninit api_object_uninit = NULL;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:	{
			do {
				hModule = LoadLibraryA("browser_hook.dll");
				if (!hModule)
					break;
				api_object_init = (tf_api_object_init)GetProcAddress(hModule, "api_object_init");
				api_object_uninit = (tf_api_object_uninit)GetProcAddress(hModule, "api_object_uninit");
				if (!api_object_init || !api_object_uninit)
					break;
				if (api_object_init(NULL,0) != 0)
					break;
			} while (0);
		}break;
		case DLL_THREAD_ATTACH:{
		}
		break;
		case DLL_THREAD_DETACH:{
		}
		break;
		case DLL_PROCESS_DETACH:{
			do{
if(!hModule)
break;
api_object_uninit();
				FreeLibrary(hModule);
				hModule = NULL;
			}while(0);
		}break;
	}
	return TRUE;
}
