#include "stdafx.h"
#include "export.h"

using namespace local;

__shared_api_ void* __stdcall api_object_init(const void*, unsigned long) {
 void* result = nullptr;
 if (Global::PluginGet())
  Global::PluginGet()->Start();
 //if (Global::PluginUIGet())
 // Global::PluginUIGet()->Start();
 return result;
}

__shared_api_ void __stdcall api_object_uninit() {
 if (Global::PluginGet())
  Global::PluginGet()->Stop();
 //if (Global::PluginUIGet())
 // Global::PluginUIGet()->Stop();
}

