/*===- libcurlpp.hpp - Wrapper for 'extern "C"' ---------------*- C -*-=======*\
|*                                                                                                                        *|
|* Part of the Chormium® Project, under the Apache License v2.0 with Chormium®          *|
|* Exceptions.                                                                                                      *|
|* See http://skstu.com/chromium/LICENSE.txt for license information.                 *|
|* SPDX-License-Identifier: Apache-2.0 WITH CHROMIUM-exception                     *|
|*                                                                                                                        *|
|*===----------------------------------------------------------------------====== *|
|*                                                                                                                        *|
|* This file is a summary of the interface for this project.                                      *|
|*                                                                                                                        *|
\*===----------------------------------------------------------------------======*/
#if !defined(__BCD1AB38_1488_4E00_AE59_F79E2A2545A2__)
#define __BCD1AB38_1488_4E00_AE59_F79E2A2545A2__
#if 0
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#endif

#include <Windows.h>

#define ENABLE_MEMADE_CHROMIUM_PLUGIN 1

#if ENABLE_MEMADE_CHROMIUM_PLUGIN
namespace chromium_plugin {
 using TypeIdentify = unsigned long long;
 using t_interface_init = void* (__stdcall*)(const void*, unsigned long);
 using t_interface_uninit = void(__stdcall*)(void);

 template<typename T>
 class InterfaceDll {
 protected:
  InterfaceDll() {}
  ~InterfaceDll() {}
 public:
  static T* CreateInterface(const std::string& module_pathname) {
   T* result = nullptr;
   HMODULE hModule = nullptr;
   do {
    if (module_pathname.empty())
     break;
    hModule = ::LoadLibraryA(module_pathname.c_str());
    if (!hModule)
     break;
    auto api_object_init = \
     reinterpret_cast<decltype(T::api_object_init)>(::GetProcAddress(hModule, "api_object_init"));
    auto api_object_uninit = \
     reinterpret_cast<decltype(T::api_object_uninit)>(::GetProcAddress(hModule, "api_object_uninit"));
    if (!api_object_init || !api_object_uninit)
     break;
    result = reinterpret_cast<decltype(result)>(api_object_init(nullptr, 0));
    if (!result)
     break;
    result->hModule = hModule;
    result->api_object_init = api_object_init;
    result->api_object_uninit = api_object_uninit;
   } while (0);
   if (nullptr == result && hModule != nullptr) {
    ::FreeLibrary(hModule);
    hModule = nullptr;
   }
   return result;
  }
  static void DestoryInterface(T*& instance) {
   do {
    if (!instance)
     break;
    if (!instance->hModule || !instance->api_object_uninit)
     break;
    HMODULE freeMod = reinterpret_cast<HMODULE>(instance->hModule);
    instance->api_object_uninit();
    instance = nullptr;
    ::FreeLibrary(freeMod);
    freeMod = nullptr;
   } while (0);
  }
 protected:
  void* hModule = nullptr;
  t_interface_init api_object_init = nullptr;
  t_interface_uninit api_object_uninit = nullptr;
 };

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 enum class EnBrowserProcessType : unsigned long long {
  EN_PROCESS_TYPE_UNKNOWN = 0x0000,
  EN_PROCESS_TYPE_MAIN = 0x1000,
  EN_PROCESS_TYPE_GPU = 0x2000,
  EN_PROCESS_TYPE_RENDERER = 0x3000,
  EN_PROCESS_TYPE_UTILITY = 0x4000,
  EN_PROCESS_TYPE_CRASHPAD = 0x5000,
 };


 class IConfig {
 public:
  virtual void Release() const = 0;
 };

 class IChromiumPlugin : public InterfaceDll<IChromiumPlugin> {
 public:
  virtual void Release() const = 0;
  virtual IConfig* ConfigGet() const = 0;
  virtual const EnBrowserProcessType& BrowserProcessType() const = 0;
  virtual bool Start() = 0;
  virtual void Stop() = 0;
 public:
  virtual void On_version_info_GetProductNameAndVersionForUserAgent(_Inout_ std::string&) = 0;
  virtual void On_version_info_GetProductNameAndVersionForReducedUserAgent(_Inout_ std::string&) = 0;
  virtual void On_version_info_GetProductName(_Inout_ std::string&) = 0;
  virtual void On_version_info_GetVersionNumber(_Inout_ std::string&) = 0;
  virtual void On_version_info_GetMajorVersionNumberAsInt(_Inout_ int&) = 0;
  virtual void On_version_info_GetMajorVersionNumber(_Inout_ std::string&) = 0;
  virtual void On_version_info_GetLastChange(_Inout_ std::string&) = 0;
  virtual void On_version_info_IsOfficialBuild(_Inout_ bool&) = 0;
  virtual void On_version_info_GetOSType(_Inout_ std::string&) = 0;
  virtual void On_version_info_GetChannelString(_Inout_ std::string&) = 0;
  virtual void On_version_info_GetSanitizerList(_Inout_ std::string&) = 0;

  virtual void On_version_base_win_GetVersionData(DWORD&, std::wstring&) = 0;
 };

}///namespace chromium_plugin

extern chromium_plugin::IChromiumPlugin* __gpMemadeChromiumPlugin;
#endif



/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 13 Feb 2023 01:29:20 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__BCD1AB38_1488_4E00_AE59_F79E2A2545A2__

