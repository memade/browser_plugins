#include "stdafx.h"
#include "export.h"
using namespace local;

__shared_api_ void __stdcall api_object_init(void** route, unsigned long& route_size) {
 __gpMain = new Main();
}

__shared_api_ void __stdcall api_object_uninit() {
 if (__gpMain)
  __gpMain->Release();
}
