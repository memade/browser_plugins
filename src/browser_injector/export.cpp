#include "stdafx.h"

__shared_api_ void* __stdcall api_object_init(const void*, unsigned long) {
 do {
  auto h = ::GetModuleHandleA("browser_hook.dll");
  if (!h)
   h = ::LoadLibraryA("browser_hook.dll");
 } while (0);
 return nullptr;
}

__shared_api_ void __stdcall api_object_uninit() {

}

