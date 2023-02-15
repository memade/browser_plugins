#include <win.h>
int main(int argc, char** argv) {
#if defined(_DEBUG)
 ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 //::_CrtSetBreakAlloc(3709);
#endif
 
 HMODULE hModule = nullptr;
 typedef  void* (__stdcall* tf_chromium_plugin_api_object_init)(const void*, unsigned long);
 typedef void(__stdcall* tf_chromium_plugin_api_object_uninit)(void);
 tf_chromium_plugin_api_object_init api_object_init = nullptr;
 tf_chromium_plugin_api_object_uninit api_object_uninit = nullptr;
 do {
  hModule = ::LoadLibraryA(R"(D:\__Github__\Windows\projects\browser_plugins\bin\x64\Debug\browser_hook.dll)");
  if (!hModule)
   break;
  api_object_init = (tf_chromium_plugin_api_object_init)::GetProcAddress(hModule, "api_object_init");
  api_object_uninit = (tf_chromium_plugin_api_object_uninit)::GetProcAddress(hModule, "api_object_uninit");
  if (!api_object_init || !api_object_uninit)
   break;
  api_object_init(nullptr, 0);
 } while (0);

 shared::Win::MainProcess(
  [&](const std::string& input, bool& exit) {

   if (input == "q") {    
    if (hModule) {
     if (api_object_uninit)
      api_object_uninit();
    }
    SK_FREE_LIBRARY(hModule);
    exit = true;
   }
   else if (input == "test") {
    SYSTEM_INFO sysInfo = { 0 };
    ::GetSystemInfo(&sysInfo);


    auto sk = 0;
   }
  });
 return 0;
}
