﻿#include "stdafx.h"

using namespace local;

__shared_api_ void* __stdcall api_object_init(const void*, unsigned long) {
 __gpCmdline = new CmdLine();
 __gpGlobal = new Global();
 return nullptr;
}

__shared_api_ void __stdcall api_object_uninit() {
 SK_DELETE_PTR(__gpGlobal);
 SK_DELETE_PTR(__gpCmdline);
}

