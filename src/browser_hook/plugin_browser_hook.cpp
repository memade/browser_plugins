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

}///namespace local