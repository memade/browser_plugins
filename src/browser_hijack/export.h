#if !defined(__1ABB7B5D_2A06_4378_8B78_72333766A29E__)
#define __1ABB7B5D_2A06_4378_8B78_72333766A29E__

#if defined(SHARED_API)
#define __shared_api_ extern "C" __declspec(dllexport)
#else
#define __shared_api_ extern "C" __declspec(dllimport)
#endif

__shared_api_ void* __stdcall api_object_init(const void*, unsigned long);
__shared_api_ void __stdcall api_object_uninit();

#if 0

OutOfProcessExceptionEventCallback @1
OutOfProcessExceptionEventDebuggerLaunchCallback @2
OutOfProcessExceptionEventSignatureCallback @3

ClearReportsBetween_ExportThunk @4
CrashForException_ExportThunk @5
DisableHook @6
DrainLog @7
DumpHungProcessWithPtype_ExportThunk @8
DumpProcessWithoutCrash @9
GetApplyHookResult @10
GetBlockedModulesCount @11
GetCrashReports_ExportThunk @12
GetCrashpadDatabasePath_ExportThunk @13
GetHandleVerifier @14
GetInstallDetailsPayload @15
GetUniqueBlockedModulesCount @16
GetUserDataDirectoryThunk @17
InjectDumpForHungInput_ExportThunk @18
IsBrowserProcess @19
IsExtensionPointDisableSet @20
IsThirdPartyInitialized @21
RegisterLogNotification @22
RequestSingleCrashUpload_ExportThunk @23
SetMetricsClientId @24
SetUploadConsent_ExportThunk @25
SignalChromeElf @26
SignalInitializeCrashReporting @27

//!@ hijack functions.
__shared_api_ void __stdcall OutOfProcessExceptionEventCallback();
__shared_api_ void __stdcall OutOfProcessExceptionEventDebuggerLaunchCallback();
__shared_api_ void __stdcall OutOfProcessExceptionEventSignatureCallback();

/*
; Copyright 2013 The Chromium Authors
; Use of this source code is governed by a BSD-style license that can be
; found in the LICENSE file.
LIBRARY  "chrome_elf.dll"

EXPORTS
  ; When functions are added to this file, they must also be added to
  ; chrome_elf_x86.def and chrome_elf_arm64.def

  ; From components/crash/core/app/crash_export_stubs.cc
  CrashForException_ExportThunk
  DumpHungProcessWithPtype_ExportThunk
  GetCrashpadDatabasePath_ExportThunk
  ClearReportsBetween_ExportThunk
  GetCrashReports_ExportThunk
  InjectDumpForHungInput_ExportThunk
  RequestSingleCrashUpload_ExportThunk
  SetUploadConsent_ExportThunk

  ; From chrome/chrome_elf/crash/crash_helper.cc
  SetMetricsClientId

  ; From chrome/chrome_elf/chrome_elf_main.cc
  DumpProcessWithoutCrash
  GetUserDataDirectoryThunk
  SignalChromeElf
  SignalInitializeCrashReporting
  IsExtensionPointDisableSet

  ; From chrome/install_static
  GetInstallDetailsPayload
  IsBrowserProcess

  ; From chrome/chrome_elf/third_party_dlls/logs.cc
  DrainLog
  RegisterLogNotification
  GetBlockedModulesCount
  GetUniqueBlockedModulesCount

  ; From chrome/chrome_elf/third_party_dlls/hook.cc
  DisableHook
  GetApplyHookResult

  ; From chrome/chrome_elf/third_party_dlls/main.cc
  IsThirdPartyInitialized
*/

__shared_api_ void* __stdcall GetHandleVerifier(void);
/*
// A function exported by the primary module, which is expected to be built with
// the "primary_module" source set.
extern "C" const install_static::InstallDetails::Payload __declspec(dllimport) *
    GetInstallDetailsPayload();
*/
__shared_api_ void* __stdcall GetInstallDetailsPayload(void);
//void ClearReportsBetween_ExportThunk(time_t begin, time_t end) {}
__shared_api_ void __stdcall ClearReportsBetween_ExportThunk(time_t begin, time_t end);
//int CrashForException_ExportThunk(EXCEPTION_POINTERS* info) {}
__shared_api_ int __stdcall CrashForException_ExportThunk(void* info);
__shared_api_ void __stdcall DisableHook(void);
/*
uint32_t DrainLog(uint8_t* buffer,
                  uint32_t buffer_size,
                  uint32_t* log_remaining)
*/
__shared_api_ std::uint32_t __stdcall DrainLog(uint8_t* buffer,
 std::uint32_t buffer_size,
 std::uint32_t* log_remaining);
//bool DumpHungProcessWithPtype_ExportThunk(HANDLE process_handle,const char* ptype) {
__shared_api_ bool __stdcall DumpHungProcessWithPtype_ExportThunk(HANDLE process_handle, const char* ptype);
__shared_api_ void __stdcall DumpProcessWithoutCrash(void);
//int32_t GetApplyHookResult()
__shared_api_ std::int32_t __stdcall GetApplyHookResult(void);
//uint32_t GetBlockedModulesCount()
__shared_api_ std::uint32_t __stdcall GetBlockedModulesCount(void);
//size_t GetCrashReports_ExportThunk(crash_reporter::Report* reports,
//size_t reports_size)
__shared_api_ size_t __stdcall GetCrashReports_ExportThunk(void* reports, size_t reports_size);
//const wchar_t* GetCrashpadDatabasePath_ExportThunk()
__shared_api_ const wchar_t* __stdcall GetCrashpadDatabasePath_ExportThunk(void);
//uint32_t GetUniqueBlockedModulesCount()
__shared_api_ std::uint32_t __stdcall GetUniqueBlockedModulesCount(void);
__shared_api_ bool __stdcall GetUserDataDirectoryThunk(wchar_t* user_data_dir,
 size_t user_data_dir_length,
 wchar_t* invalid_user_data_dir,
 size_t invalid_user_data_dir_length);
//HANDLE InjectDumpForHungInput_ExportThunk(HANDLE process)
__shared_api_ HANDLE __stdcall InjectDumpForHungInput_ExportThunk(HANDLE process);
__shared_api_ bool __stdcall IsBrowserProcess(void);
__shared_api_ bool __stdcall IsExtensionPointDisableSet(void);
//bool IsThirdPartyInitialized()
__shared_api_ bool __stdcall IsThirdPartyInitialized(void);
//bool RegisterLogNotification(HANDLE event_handle)
__shared_api_ bool __stdcall RegisterLogNotification(HANDLE event_handle);
//void RequestSingleCrashUpload_ExportThunk(const char* local_id) {}
__shared_api_ void __stdcall RequestSingleCrashUpload_ExportThunk(const char* local_id);
//void SetMetricsClientIdImpl(const char* client_id);
__shared_api_ void __stdcall SetMetricsClientId(const char* client_id);
//void SetUploadConsent_ExportThunk(bool consent) {}
__shared_api_ void __stdcall SetUploadConsent_ExportThunk(bool consent);
__shared_api_ void __stdcall SignalChromeElf(void);
__shared_api_ void __stdcall SignalInitializeCrashReporting(void);
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 29 Jan 2023 14:25:35 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__1ABB7B5D_2A06_4378_8B78_72333766A29E__
