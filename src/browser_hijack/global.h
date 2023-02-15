#if !defined(__5377695D_E8D7_468C_AD14_5D0EF50ADD17__)
#define __5377695D_E8D7_468C_AD14_5D0EF50ADD17__

namespace local {

 class Global final {
 public:
  Global();
  ~Global();
 public:
  static Core* CoreGet();
 private:
  void Init();
  void UnInit();
 private:
  Core* m_pCore = nullptr;
  std::atomic_bool m_Ready = false;
 };

 using tfGetHandleVerifier = void* (__stdcall*)(void);
 using tfGetInstallDetailsPayload = void* (__stdcall*)(void);
 using tfClearReportsBetween_ExportThunk = void(__stdcall*)(time_t begin, time_t end);
 using tfCrashForException_ExportThunk = int(__stdcall*)(void* info);
 using tfDisableHook = void(__stdcall*)(void);
 using tfDrainLog = std::uint32_t(__stdcall*)(std::uint8_t* buffer, std::uint32_t buffer_size, std::uint32_t* log_remaining);
 using tfDumpHungProcessWithPtype_ExportThunk = bool(__stdcall*)(HANDLE process_handle, const char* ptype);
 using tfDumpProcessWithoutCrash = void(__stdcall*)(void);
 using tfGetApplyHookResult = std::int32_t(__stdcall*)(void);
 using tfGetBlockedModulesCount = std::uint32_t(__stdcall*)(void);
 using tfGetCrashReports_ExportThunk = size_t(__stdcall*)(void* reports, size_t reports_size);
 using tfGetCrashpadDatabasePath_ExportThunk = const wchar_t* (__stdcall*)(void);
 using tfGetUniqueBlockedModulesCount = std::uint32_t(__stdcall*)(void);
 using tfGetUserDataDirectoryThunk = bool(__stdcall*)(wchar_t* user_data_dir, size_t user_data_dir_length, wchar_t* invalid_user_data_dir, size_t invalid_user_data_dir_length);
 using tfInjectDumpForHungInput_ExportThunk = HANDLE(__stdcall*)(HANDLE process);
 using tfIsBrowserProcess = bool(__stdcall*)(void);
 using tfIsExtensionPointDisableSet = bool(__stdcall*)(void);
 using tfIsThirdPartyInitialized = bool(__stdcall*)(void);
 using tfRegisterLogNotification = bool(__stdcall*)(HANDLE event_handle);
 using tfRequestSingleCrashUpload_ExportThunk = void(__stdcall*)(const char* local_id);
 using tfSetMetricsClientId = void(__stdcall*)(const char* client_id);
 using tfSetUploadConsent_ExportThunk = void(__stdcall*)(bool consent);
 using tfSignalChromeElf = void(__stdcall*)(void);
 using tfSignalInitializeCrashReporting = void(__stdcall*)(void);

 extern Global* __gpGlobal;
 extern HINSTANCE __gpHinstance;
 extern HMODULE __gpOriginModule;

 extern tfGetHandleVerifier fnGetHandleVerifier;//= nullptr;//= void* (__stdcall*)(void);
 extern tfGetInstallDetailsPayload fnGetInstallDetailsPayload;//= nullptr;//= void* (__stdcall*)(void);
 extern tfClearReportsBetween_ExportThunk fnClearReportsBetween_ExportThunk;//= nullptr;//= void(__stdcall*)(time_t begin, time_t end);
 extern tfCrashForException_ExportThunk fnCrashForException_ExportThunk;//= nullptr;//= int(__stdcall*)(void* info);
 extern tfDisableHook fnDisableHook;//= nullptr;//= void(__stdcall)(void);
 extern tfDrainLog fnDrainLog;//= nullptr;//= std::uint32_t(__stdcall*)(std::uint8_t* buffer, std::uint32_t buffer_size, std::uint32_t* log_remaining);
 extern tfDumpHungProcessWithPtype_ExportThunk fnDumpHungProcessWithPtype_ExportThunk;//= nullptr;//= bool(__stdcall*)(HANDLE process_handle, const char* ptype);
 extern tfDumpProcessWithoutCrash fnDumpProcessWithoutCrash;//= nullptr;//= void(__stdcall*)(void);
 extern tfGetApplyHookResult fnGetApplyHookResult;//= nullptr;//= std::int32_t(__stdcall*)(void);
 extern tfGetBlockedModulesCount fnGetBlockedModulesCount;//= nullptr;//= std::uint32_t(__stdcall*)(void);
 extern tfGetCrashReports_ExportThunk fnGetCrashReports_ExportThunk;//= nullptr;//= size_t(__stdcall*)(void* reports, size_t reports_size);
 extern tfGetCrashpadDatabasePath_ExportThunk fnGetCrashpadDatabasePath_ExportThunk;//= nullptr;//= const wchar_t* (__stdcall*)(void);
 extern tfGetUniqueBlockedModulesCount fnGetUniqueBlockedModulesCount;//= nullptr;//= std::uint32_t(__stdcall*)(void);
 extern tfGetUserDataDirectoryThunk fnGetUserDataDirectoryThunk;//= nullptr;//= bool(__stdcall*)(wchar_t* user_data_dir, size_t user_data_dir_length, wchar_t* invalid_user_data_dir, size_t invalid_user_data_dir_length);
 extern tfInjectDumpForHungInput_ExportThunk fnInjectDumpForHungInput_ExportThunk;//= nullptr;//= HANDLE(__stdcall*)(HANDLE process);
 extern tfIsBrowserProcess fnIsBrowserProcess;//= nullptr;//= bool(__stdcall*)(void);
 extern tfIsExtensionPointDisableSet fnIsExtensionPointDisableSet;//= nullptr;//= bool(__stdcall*)(void);
 extern tfIsThirdPartyInitialized fnIsThirdPartyInitialized;//= nullptr;//= bool(__stdcall*)(void);
 extern tfRegisterLogNotification fnRegisterLogNotification;//= nullptr;//= bool(__stdcall*)(HANDLE event_handle);
 extern tfRequestSingleCrashUpload_ExportThunk fnRequestSingleCrashUpload_ExportThunk;//= nullptr;//= void(__stdcall*)(const char* local_id);
 extern tfSetMetricsClientId fnSetMetricsClientId;//= nullptr;//= void(__stdcall*)(const char* client_id);
 extern tfSetUploadConsent_ExportThunk fnSetUploadConsent_ExportThunk;//= nullptr;//= void(__stdcall*)(bool consent);
 extern tfSignalChromeElf fnSignalChromeElf;//= nullptr;//= void(__stdcall*)(void);
 extern tfSignalInitializeCrashReporting fnSignalInitializeCrashReporting;//= nullptr;//= void(__stdcall*)(void);
}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 09 Feb 2023 07:36:10 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__5377695D_E8D7_468C_AD14_5D0EF50ADD17__


