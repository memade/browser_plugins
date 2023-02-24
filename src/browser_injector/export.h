#if !defined(__1ABB7B5D_2A06_4378_8B78_72333766A29E__)
#define __1ABB7B5D_2A06_4378_8B78_72333766A29E__

#if defined(SHARED_API)
#define __shared_api_ extern "C" __declspec(dllexport)
#else
#define __shared_api_ extern "C" __declspec(dllimport)
#endif

__shared_api_ void* __stdcall api_object_init(const void*, unsigned long);
__shared_api_ void __stdcall api_object_uninit();

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 29 Jan 2023 14:25:35 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__1ABB7B5D_2A06_4378_8B78_72333766A29E__
