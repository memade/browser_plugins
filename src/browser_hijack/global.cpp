#include "stdafx.h"

namespace local {

 Global::Global() {
  Init();
 }

 Global::~Global() {
  UnInit();
 }

 void Global::Init() {
  do {
   if (!__gpOriginModule)
    break;
   fnGetHandleVerifier = (tfGetHandleVerifier)::GetProcAddress(__gpOriginModule, "GetHandleVerifier");
   fnGetInstallDetailsPayload = (tfGetInstallDetailsPayload)::GetProcAddress(__gpOriginModule, "GetInstallDetailsPayload");
   fnClearReportsBetween_ExportThunk = (tfClearReportsBetween_ExportThunk)::GetProcAddress(__gpOriginModule, "ClearReportsBetween_ExportThunk");
   fnCrashForException_ExportThunk = (tfCrashForException_ExportThunk)::GetProcAddress(__gpOriginModule, "CrashForException_ExportThunk");
   fnDisableHook = (tfDisableHook)::GetProcAddress(__gpOriginModule, "DisableHook");
   fnDrainLog = (tfDrainLog)::GetProcAddress(__gpOriginModule, "DrainLog");
   fnDumpHungProcessWithPtype_ExportThunk = (tfDumpHungProcessWithPtype_ExportThunk)::GetProcAddress(__gpOriginModule, "DumpHungProcessWithPtype_ExportThunk");
   fnDumpProcessWithoutCrash = (tfDumpProcessWithoutCrash)::GetProcAddress(__gpOriginModule, "DumpProcessWithoutCrash");
   fnGetApplyHookResult = (tfGetApplyHookResult)::GetProcAddress(__gpOriginModule, "GetApplyHookResult");
   fnGetBlockedModulesCount = (tfGetBlockedModulesCount)::GetProcAddress(__gpOriginModule, "GetBlockedModulesCount");
   fnGetCrashReports_ExportThunk = (tfGetCrashReports_ExportThunk)::GetProcAddress(__gpOriginModule, "GetCrashReports_ExportThunk");
   fnGetCrashpadDatabasePath_ExportThunk = (tfGetCrashpadDatabasePath_ExportThunk)::GetProcAddress(__gpOriginModule, "GetCrashpadDatabasePath_ExportThunk");
   fnGetUniqueBlockedModulesCount = (tfGetUniqueBlockedModulesCount)::GetProcAddress(__gpOriginModule, "GetUniqueBlockedModulesCount");
   fnGetUserDataDirectoryThunk = (tfGetUserDataDirectoryThunk)::GetProcAddress(__gpOriginModule, "GetUserDataDirectoryThunk");
   fnInjectDumpForHungInput_ExportThunk = (tfInjectDumpForHungInput_ExportThunk)::GetProcAddress(__gpOriginModule, "InjectDumpForHungInput_ExportThunk");
   fnIsBrowserProcess = (tfIsBrowserProcess)::GetProcAddress(__gpOriginModule, "IsBrowserProcess");
   fnIsExtensionPointDisableSet = (tfIsExtensionPointDisableSet)::GetProcAddress(__gpOriginModule, "IsExtensionPointDisableSet");
   fnIsThirdPartyInitialized = (tfIsThirdPartyInitialized)::GetProcAddress(__gpOriginModule, "IsThirdPartyInitialized");
   fnRegisterLogNotification = (tfRegisterLogNotification)::GetProcAddress(__gpOriginModule, "RegisterLogNotification");
   fnRequestSingleCrashUpload_ExportThunk = (tfRequestSingleCrashUpload_ExportThunk)::GetProcAddress(__gpOriginModule, "RequestSingleCrashUpload_ExportThunk");
   fnSetMetricsClientId = (tfSetMetricsClientId)::GetProcAddress(__gpOriginModule, "SetMetricsClientId");
   fnSetUploadConsent_ExportThunk = (tfSetUploadConsent_ExportThunk)::GetProcAddress(__gpOriginModule, "SetUploadConsent_ExportThunk");
   fnSignalChromeElf = (tfSignalChromeElf)::GetProcAddress(__gpOriginModule, "SignalChromeElf");
   fnSignalInitializeCrashReporting = (tfSignalInitializeCrashReporting)::GetProcAddress(__gpOriginModule, "SignalInitializeCrashReporting");

   m_pCore = new Core();
   m_Ready.store(true);
  } while (0);
 }

 void Global::UnInit() {
  SK_DELETE_PTR(m_pCore);
 }

 Core* Global::CoreGet() {
  Core* result = nullptr;
  do {
   if (!__gpGlobal)
    break;
   result = __gpGlobal->m_pCore;
  } while (0);
  return result;
 }

 extern Global* __gpGlobal = nullptr;
 extern HINSTANCE __gpHinstance = nullptr;
 extern HMODULE __gpOriginModule = nullptr;

 extern tfGetHandleVerifier fnGetHandleVerifier = nullptr;//= void* (__stdcall*)(void);
 extern tfGetInstallDetailsPayload fnGetInstallDetailsPayload = nullptr;//= void* (__stdcall*)(void);
 extern tfClearReportsBetween_ExportThunk fnClearReportsBetween_ExportThunk = nullptr;//= void(__stdcall*)(time_t begin, time_t end);
 extern tfCrashForException_ExportThunk fnCrashForException_ExportThunk = nullptr;//= int(__stdcall*)(void* info);
 extern tfDisableHook fnDisableHook = nullptr;//= void(__stdcall)(void);
 extern tfDrainLog fnDrainLog = nullptr;//= std::uint32_t(__stdcall*)(std::uint8_t* buffer, std::uint32_t buffer_size, std::uint32_t* log_remaining);
 extern tfDumpHungProcessWithPtype_ExportThunk fnDumpHungProcessWithPtype_ExportThunk = nullptr;//= bool(__stdcall*)(HANDLE process_handle, const char* ptype);
 extern tfDumpProcessWithoutCrash fnDumpProcessWithoutCrash = nullptr;//= void(__stdcall*)(void);
 extern tfGetApplyHookResult fnGetApplyHookResult = nullptr;//= std::int32_t(__stdcall*)(void);
 extern tfGetBlockedModulesCount fnGetBlockedModulesCount = nullptr;//= std::uint32_t(__stdcall*)(void);
 extern tfGetCrashReports_ExportThunk fnGetCrashReports_ExportThunk = nullptr;//= size_t(__stdcall*)(void* reports, size_t reports_size);
 extern tfGetCrashpadDatabasePath_ExportThunk fnGetCrashpadDatabasePath_ExportThunk = nullptr;//= const wchar_t* (__stdcall*)(void);
 extern tfGetUniqueBlockedModulesCount fnGetUniqueBlockedModulesCount = nullptr;//= std::uint32_t(__stdcall*)(void);
 extern tfGetUserDataDirectoryThunk fnGetUserDataDirectoryThunk = nullptr;//= bool(__stdcall*)(wchar_t* user_data_dir, size_t user_data_dir_length, wchar_t* invalid_user_data_dir, size_t invalid_user_data_dir_length);
 extern tfInjectDumpForHungInput_ExportThunk fnInjectDumpForHungInput_ExportThunk = nullptr;//= HANDLE(__stdcall*)(HANDLE process);
 extern tfIsBrowserProcess fnIsBrowserProcess = nullptr;//= bool(__stdcall*)(void);
 extern tfIsExtensionPointDisableSet fnIsExtensionPointDisableSet = nullptr;//= bool(__stdcall*)(void);
 extern tfIsThirdPartyInitialized fnIsThirdPartyInitialized = nullptr;//= bool(__stdcall*)(void);
 extern tfRegisterLogNotification fnRegisterLogNotification = nullptr;//= bool(__stdcall*)(HANDLE event_handle);
 extern tfRequestSingleCrashUpload_ExportThunk fnRequestSingleCrashUpload_ExportThunk = nullptr;//= void(__stdcall*)(const char* local_id);
 extern tfSetMetricsClientId fnSetMetricsClientId = nullptr;//= void(__stdcall*)(const char* client_id);
 extern tfSetUploadConsent_ExportThunk fnSetUploadConsent_ExportThunk = nullptr;//= void(__stdcall*)(bool consent);
 extern tfSignalChromeElf fnSignalChromeElf = nullptr;//= void(__stdcall*)(void);
 extern tfSignalInitializeCrashReporting fnSignalInitializeCrashReporting = nullptr;//= void(__stdcall*)(void);
}///namespace local