#include "stdafx.h"

namespace local {

#if 0
	namespace memade {
		template<typename TFunction>
		bool TChromiumHook(
			const char* function_name,
			void** route,
			size_t& route_size,
			const void* original_view = nullptr,
			const char* hook_module_name = "browser_hook.dll"
		) {
			bool result = false;
			do {
				if (!function_name || !hook_module_name)
					break;
				HMODULE hModule = ::GetModuleHandleA(hook_module_name);
				if (!hModule)
					break;
				TFunction fun = (TFunction)::GetProcAddress(hModule, function_name);
				if (!fun)
					break;
				result = fun(route, route_size, original_view);
} while (0);
return result;
 }
}///namespace memade
#endif

 //!@ Chromium : [int Screen::availWidth() cons ]
 __shared_api_ bool __stdcall hook_Screen_availWidth(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  bool result = 0;
  int original_size = 0;
  do {
   if (!__gpGlobal)
    break;
   if (!view)
    break;
   
   memcpy(&original_size, view, sizeof(original_size));  
   auto value = __gpGlobal->PluginDataGet().available_screen_size;
   if (value <= 0)
    break;
   original_size -= value;
   route_size = sizeof(original_size);
   *route = HeapAlloc(GetProcessHeap(), 0, route_size);
   memcpy(*route, &original_size, route_size);
   result = true;
  } while (0);
  return result;
 }
 //!@ Chromium : [int Screen::availHeight() const]
 __shared_api_ bool __stdcall hook_Screen_availHeight(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  do {


  } while (0);
  return false;
 }
 //!@ Chromium : [int Screen::width() const]
 __shared_api_ bool __stdcall hook_Screen_width(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  do {


  } while (0);
  return false;
 }
 //!@ Chromium : [int Screen::height() const]
 __shared_api_ bool __stdcall hook_Screen_height(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  do {


  } while (0);
  return false;
 }


 __shared_api_ bool __stdcall hook_ChromeContentBrowserClient_GetUserAgent(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  std::string origin_useragent;
  std::string hook_useragent;
  do {


  } while (0);
  return false;
 }

 //HP-UX
//Linux i686
//Linux armv7l
//Mac68K
//MacPPC
//MacIntel
//SunOS
//Win16
//Win32
//WinCE
//iPhone
//iPod
//iPad
//Android
//BlackBerry
//Opera
//!@ https://pixelscan.net/ -- [Platform]
 __shared_api_ bool __stdcall hook_NavigatorPlatform(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  std::string original_data;//!@ Win32
  do {
   if (view)
    original_data = (const char*)view;


  } while (0);
  return false;
 }

 __shared_api_ bool __stdcall hook_NavigatorGetAcceptLanguages(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  std::string original_data;//!@ zh-CN,zh
  do {
   if (view)
    original_data = (const char*)view;





  } while (0);
  return false;
 }

//!@ hook_WebGLRenderingContextBase_getParameter
//!@ view : original entry parameter[pname : uint32_t]
//!@ route :  original result value [return : string]
//!@ route_size : original result value size
//!@ https://pixelscan.net/ -- [WebGL version]
 __shared_api_ bool __stdcall hook_getParameter_GL_VENDOR(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  bool result = false;
  std::string original_data;//!@ [WebGL 1.0 (OpenGL ES 2.0 Chromium)]
  do {
   if (view)
    original_data = (const char*)view;

   //*route = HeapAlloc(GetProcessHeap(), 0, route_size);
   //route_size = 200;
   //result = true;
  } while (0);
  return result;
 }
 //!@ hook_WebGLRenderingContextBase_getParameter
 //!@ view : original entry parameter[pname : uint32_t]
 //!@ route :  original result value [return : string]
 //!@ route_size : original result value size
 //!@ https://pixelscan.net/ -- [WebGL unmasked vendor]
 __shared_api_ bool __stdcall hook_getParameter_UnmaskedRendererWebgl(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  bool result = false;
  std::string original_data;//!@ [Google Inc. (NVIDIA)]
  do {
   if (view)
    original_data = (const char*)view;

   //*route = HeapAlloc(GetProcessHeap(), 0, route_size);
   //route_size = 200;
   //result = true;
  } while (0);
  return result;
 }
 //!@ https://pixelscan.net/ -- [WebGL unmasked renderer]
 __shared_api_ bool __stdcall hook_getParameter_UnmaskedVendorWebgl(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {
  
  bool result = false;
  std::string original_data;//!@ [ANGLE (NVIDIA, NVIDIA GeForce RTX 2060 SUPER Direct3D11 vs_5_0 ps_5_0, D3D11)]
  do {
   if (view)
    original_data = (const char*)view;

   //*route = HeapAlloc(GetProcessHeap(), 0, route_size);
   //route_size = 200;
   //result = true;
  } while (0);
  return result;
 }

 //!@ https://pixelscan.net/ -- [HardwareConcurency]
 __shared_api_ bool __stdcall hook_hardwareConcurrency(_Inout_ void** route, _Inout_ size_t& route_size, _In_ const void* view) {  
  bool result = false;
  unsigned int original_data = 0;//!@ [8]
  do {
   if (view)
    memcpy(&original_data, view, sizeof(original_data));
   unsigned int count = static_cast<unsigned int>(__gpGlobal->PluginDataGet().hardware_concurency);
   route_size = sizeof(count);
   *route = HeapAlloc(GetProcessHeap(), 0, route_size);
   memcpy(*route, &count, route_size);
   result = true;
  } while (0);
  return result;
 }
 //__shared_api_ bool __stdcall hook_ChromeContentBrowserClient_GetUserAgent(void**, size_t&, const void* view) {
 // const char* user_agent_productname_and_version = "Memade/100.0.0";
 // route_size = strlen(user_agent_productname_and_version);
 // *route = HeapAlloc(GetProcessHeap(), 0, route_size);
 // memcpy(*route, user_agent_productname_and_version, route_size);
 //}



 __shared_api_ bool __stdcall hook_SysInfoUptime(void** route, size_t& route_size, const void* view) {

  std::int64_t original = 0;
  do {
   if (view)
    ::memcpy(&original, view, sizeof(std::int64_t));
  } while (0);
  LOGINFO("{} view({}).", __FUNCTION__, original);
  return false;
 }
 __shared_api_ bool __stdcall hook_SysInfoProcessCPUArchitecture(void** route, size_t& route_size, const void* view) {
  const char* original = (const char*)view;
  do {
  } while (0);
  LOGINFO("{} view({}).", __FUNCTION__, original);
  return false;
 }
 __shared_api_ bool __stdcall hook_SysInfoAmountOfAvailablePhysicalMemory(void** route, size_t& route_size, const void* view) {
  std::uint64_t original = 0;
  do {
   if (view)
    ::memcpy(&original, view, sizeof(std::uint64_t));
  } while (0);
  LOGINFO("{} view({}).", __FUNCTION__, original);
  return false;
 }
 __shared_api_ bool __stdcall hook_SysInfoAmountOfPhysicalMemory(void** route, size_t& route_size, const void* view) {
  std::uint64_t original = 0;
  do {
   if (view)
    ::memcpy(&original, view, sizeof(std::uint64_t));
  } while (0);
  LOGINFO("{} view({}).", __FUNCTION__, original);
  return false;
 }
 __shared_api_ bool __stdcall hook_SysInfoNumberOfEfficientProcessors(void** route, size_t& route_size, const void* view) {
  int original = 0;
  do {
   if (view)
    ::memcpy(&original, view, sizeof(int));
   
  } while (0);
  LOGINFO("{} view({}).", __FUNCTION__, original);
  return false;
 }
 __shared_api_ bool __stdcall hook_GetProductName(void** route, size_t& route_size, const void* view) {
  return false;
  const char* product_name = "Memade";
  route_size = strlen(product_name);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);  
  memcpy(*route, product_name, route_size);
 }
 __shared_api_ bool __stdcall hook_GetVersionNumber(void** route, size_t& route_size, const void* view) {
  return false;
  /*
  112.0.5584.0
  */
  const char* version_number = "100.0.0.0";
  route_size = strlen(version_number);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, version_number, route_size);
 }
 __shared_api_ bool __stdcall hook_GetProductNameAndVersionForReducedUserAgent(void** route, size_t& route_size, const void* view) {
  return false;
  /*
  Chromium : Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/112.0.0.0 Safari/537.36
  Google Chrome : Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36
  Microsoft Edge : Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36 Edg/110.0.1587.41
  */
  const char* user_agent_productname_and_version = "Memade/100.0.0";
  route_size = strlen(user_agent_productname_and_version);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, user_agent_productname_and_version, route_size);
 }
 __shared_api_ bool __stdcall hook_GetMajorVersionNumberAsInt(void** route, size_t& route_size, const void* view) {
  return false;
/*
100
*/
  int major_version_number_as_int = 100;
  route_size = sizeof(int);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, &major_version_number_as_int, route_size);
 }

 __shared_api_ bool __stdcall hook_GetLastChange(void** route, size_t& route_size, const void* view) {
  //return false;
  /*4103ce089ac196ef7817d207ac19e54b8613a104-refs/heads/main@{#1102596}
  */
  const char* last_change = "1EC096E2-D918-410A-8BC9-21DC1C1710DE@{#1000000}";
  route_size = strlen(last_change);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, last_change, route_size);
  return true;
 }

 __shared_api_ bool __stdcall hook_IsOfficialBuild(void** route, size_t& route_size, const void* view) {
  return false;
  bool is_official_build = false;
  route_size = sizeof(bool);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, &is_official_build, route_size);
 }

 __shared_api_ bool __stdcall hook_GetOSType(void** route, size_t& route_size, const void* view) {
  return false;
  const char* os_type = "OpenBSD";
  route_size = strlen(os_type);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, os_type, route_size);
 }

 __shared_api_ bool __stdcall hook_GetSanitizerList(void** route, size_t& route_size, const void* view) {
  return false;
#if 0
  const char* sanitizer_list = "Chromium OS";
  route_size = strlen(sanitizer_list);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, sanitizer_list, route_size);
#endif
 }

 __shared_api_ bool __stdcall hook_GetVersionDataReleaseId(void** route, size_t& route_size, const void* view) {
  return false;
 /*
 Windows 11 Version 22H2 (Build 22621.1105) 
 22H2
 */
  const wchar_t* release_id = L"21H1";
  route_size = wcslen(release_id);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size * sizeof(wchar_t));
  memcpy(*route, release_id, route_size * sizeof(wchar_t));
  return true;
 }

 __shared_api_ bool __stdcall hook_GetVersionDataUbr(void** route, size_t& route_size, const void* view) {
  return false;
  /*
  Windows 11 Version 22H2 (Build 22621.1105) 
  1105
  */
  DWORD ubr = 1108;
  route_size = sizeof(ubr);
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, &ubr, sizeof(ubr));
  return true;
 }

 __shared_api_ bool __stdcall hook_UrlLoaderUploadElementReaderBytes(_Inout_ void** request_body, _Inout_ size_t& request_body_size, _In_ const void* request_url) {
  bool result = false;
  do {
   if (!request_url)
    break;
   std::string origin_request_url(request_url ? (const char*)request_url : "");
   if (origin_request_url.empty())
    break;
   if (origin_request_url.find(R"(pixelscan.net)") == std::string::npos)
    break;
   std::string origin_request_body;
   std::string new_request_body;
   if (*request_body && request_body_size > 0)
    origin_request_body.append((char*)(*request_body), request_body_size);
   *request_body = nullptr;
   request_body_size = 0;
   do {
    if (new_request_body.empty())
     break;
    request_body_size = new_request_body.size();
    *request_body = HeapAlloc(GetProcessHeap(), 0, new_request_body.size());
    if (!(*request_body))
     break;
    memcpy(*request_body, new_request_body.data(), new_request_body.size());

    //std::string asflkjasdkfl = "asdlgkhas;lgaldsghk";
    //std::vector<std::uint8_t> changed;
    //for (size_t i = 0; i < request_body_size; ++i)
    // changed.push_back(asflkjasdkfl[i]);
    result = true;
   } while (0);
  } while (0);

  return result;
 }
}///namespace local