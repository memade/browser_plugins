#include "stdafx.h"
#include "export.h"
using namespace local;
__shared_api_ void __stdcall api_object_init(void**, size_t&) {
 std::string current_process_path = shared::Win::GetModulePathA();
 if (!__gpPlugin) {
  __gpPlugin = new Plugin();
  __gpPlugin->Start();
 }
}

__shared_api_ void __stdcall api_object_uninit() {
 if (__gpPlugin) {
  __gpPlugin->Stop();
  __gpPlugin->Release();
  __gpPlugin = nullptr;
 }
}
