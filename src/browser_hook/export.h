#if !defined(__1ABB7B5D_2A06_4378_8B78_72333766A29E__)
#define __1ABB7B5D_2A06_4378_8B78_72333766A29E__

#if defined(SHARED_API)
#define __shared_api_ extern "C" __declspec(dllexport)
#else
#define __shared_api_ extern "C" __declspec(dllimport)
#endif

__shared_api_ void* __stdcall api_object_init(const void*, unsigned long);
__shared_api_ void __stdcall api_object_uninit();

__shared_api_ bool __stdcall hook_ChromeContentBrowserClient_GetUserAgent(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [ case WebGLDebugRendererInfo::kUnmaskedRendererWebgl: ]
//!@ view : const char*
__shared_api_ bool __stdcall hook_getParameter_UnmaskedRendererWebgl(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [ case WebGLDebugRendererInfo::kUnmaskedVendorWebgl: ]
//!@ view : const char*
__shared_api_ bool __stdcall hook_getParameter_UnmaskedVendorWebgl(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [case GL_VENDOR: ]
//!@ view : const char* 
__shared_api_ bool __stdcall hook_getParameter_GL_VENDOR(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [unsigned NavigatorConcurrentHardware::hardwareConcurrency() const]
//!@ view : unsigned int
__shared_api_ bool __stdcall hook_hardwareConcurrency(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [String Navigator::platform() const]
//!@ view : const char*
__shared_api_ bool __stdcall hook_NavigatorPlatform(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [String Navigator::GetAcceptLanguages()]
//!@ view : const char*
__shared_api_ bool __stdcall hook_NavigatorGetAcceptLanguages(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [int Screen::availWidth() cons ]
__shared_api_ bool __stdcall hook_Screen_availWidth(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [int Screen::availHeight() const]
__shared_api_ bool __stdcall hook_Screen_availHeight(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [int Screen::width() const]
__shared_api_ bool __stdcall hook_Screen_width(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);
//!@ Chromium : [int Screen::height() const]
__shared_api_ bool __stdcall hook_Screen_height(_Inout_ void**, _Inout_ size_t&, _In_ const void* view);












__shared_api_ bool __stdcall hook_GetProductName(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_GetVersionNumber(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_GetLastChange(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_IsOfficialBuild(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_GetProductNameAndVersionForReducedUserAgent(void**, size_t&,const void* view);
__shared_api_ bool __stdcall hook_GetMajorVersionNumberAsInt(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_GetOSType(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_GetSanitizerList(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_GetVersionDataReleaseId(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_GetVersionDataUbr(void**, size_t&, const void* view);

__shared_api_ bool __stdcall hook_SysInfoNumberOfEfficientProcessors(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_SysInfoAmountOfPhysicalMemory(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_SysInfoAmountOfAvailablePhysicalMemory(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_SysInfoProcessCPUArchitecture(void**, size_t&, const void* view);
__shared_api_ bool __stdcall hook_SysInfoUptime(void**, size_t&, const void* view);

__shared_api_ bool __stdcall hook_UrlLoaderUploadElementReaderBytes(_Inout_ void** request_body, _Inout_ size_t& request_body_size, _In_ const void* request_url);
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 29 Jan 2023 14:25:35 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__1ABB7B5D_2A06_4378_8B78_72333766A29E__
