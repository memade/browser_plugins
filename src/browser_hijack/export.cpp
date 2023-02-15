#include "stdafx.h"
#include "export.h"

using namespace local;

__shared_api_ void* __stdcall api_object_init(const void*, unsigned long) {
 void* result = nullptr;
 do {

 } while (0);
 return result;
}

__shared_api_ void __stdcall api_object_uninit() {

}

#if 0
__shared_api_ void __stdcall OutOfProcessExceptionEventCallback() {
 ::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
}
__shared_api_ void __stdcall OutOfProcessExceptionEventDebuggerLaunchCallback() {
 ::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
}
__shared_api_ void __stdcall OutOfProcessExceptionEventSignatureCallback() {
 ::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
}

__shared_api_ void __stdcall ClearReportsBetween_ExportThunk(time_t begin, time_t end) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnClearReportsBetween_ExportThunk(begin, end);
}
__shared_api_ int __stdcall CrashForException_ExportThunk(void* info) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnCrashForException_ExportThunk(info);
}
__shared_api_ void __stdcall DisableHook(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnDisableHook();
}
__shared_api_ std::uint32_t __stdcall DrainLog(uint8_t* buffer,
 std::uint32_t buffer_size,
 std::uint32_t* log_remaining) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnDrainLog(buffer, buffer_size, log_remaining);
}
__shared_api_ bool __stdcall DumpHungProcessWithPtype_ExportThunk(HANDLE process_handle, const char* ptype) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return false;
 return fnDumpHungProcessWithPtype_ExportThunk(process_handle, ptype);
}
__shared_api_ void __stdcall DumpProcessWithoutCrash(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnDumpProcessWithoutCrash();
}
__shared_api_ std::int32_t __stdcall GetApplyHookResult(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return 0;
 return fnGetApplyHookResult();
}
__shared_api_ std::uint32_t __stdcall GetBlockedModulesCount(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return 0;
 return fnGetBlockedModulesCount();
}
__shared_api_ size_t __stdcall GetCrashReports_ExportThunk(void* reports, size_t reports_size) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return 0;
 return fnGetCrashReports_ExportThunk(reports, reports_size);
}
__shared_api_ const wchar_t* __stdcall GetCrashpadDatabasePath_ExportThunk(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return nullptr;
 return fnGetCrashpadDatabasePath_ExportThunk();
}
__shared_api_ void* __stdcall GetHandleVerifier(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return nullptr;
 return fnGetHandleVerifier();
}
__shared_api_ void* __stdcall GetInstallDetailsPayload(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return nullptr;
 return fnGetInstallDetailsPayload();
}
__shared_api_ std::uint32_t __stdcall GetUniqueBlockedModulesCount(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return 0;
 return fnGetUniqueBlockedModulesCount();
}
__shared_api_ bool __stdcall GetUserDataDirectoryThunk(wchar_t* user_data_dir,
 size_t user_data_dir_length,
 wchar_t* invalid_user_data_dir,
 size_t invalid_user_data_dir_length) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return false;
 return fnGetUserDataDirectoryThunk(user_data_dir, user_data_dir_length, invalid_user_data_dir, invalid_user_data_dir_length);
}
__shared_api_ HANDLE __stdcall InjectDumpForHungInput_ExportThunk(HANDLE process) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return nullptr;
 return fnInjectDumpForHungInput_ExportThunk(process);
}
__shared_api_ bool __stdcall IsBrowserProcess(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return false;
 return fnIsBrowserProcess();
}
__shared_api_ bool __stdcall IsExtensionPointDisableSet(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return false;
 return fnIsExtensionPointDisableSet();
}
__shared_api_ bool __stdcall IsThirdPartyInitialized(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return false;
 return fnIsThirdPartyInitialized();
}
__shared_api_ bool __stdcall RegisterLogNotification(HANDLE event_handle) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 //return false;
 return fnRegisterLogNotification(event_handle);
}
__shared_api_ void __stdcall RequestSingleCrashUpload_ExportThunk(const char* local_id) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnRequestSingleCrashUpload_ExportThunk(local_id);
}
__shared_api_ void __stdcall SetMetricsClientId(const char* client_id) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnSetMetricsClientId(client_id);
}
__shared_api_ void __stdcall SetUploadConsent_ExportThunk(bool consent) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnSetUploadConsent_ExportThunk(consent);
}
__shared_api_ void __stdcall SignalChromeElf(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnSignalChromeElf();
}
__shared_api_ void __stdcall SignalInitializeCrashReporting(void) {
 //::MessageBoxA(NULL, __FUNCDNAME__, NULL, NULL);
 return fnSignalInitializeCrashReporting();
}
#endif