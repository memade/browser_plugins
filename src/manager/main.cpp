#include "stdafx.h"

int WINAPI wWinMain(
 _In_ HINSTANCE hInstance,
 _In_opt_ HINSTANCE hPrevInstance,
 _In_ LPWSTR lpCmdLine,
 _In_ int nShowCmd) {

 UNREFERENCED_PARAMETER(hPrevInstance);
 UNREFERENCED_PARAMETER(lpCmdLine);

#if defined(_DEBUG)
 ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 //::_CrtSetBreakAlloc(255);
#endif
 local::__gpHinstance = hInstance;
 local::__gpGlobal = new local::Global();

 local::__gpGlobal->ConfigGet()->Init();

 local::UIApp ui_app;
 ui_app.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

 SK_DELETE_PTR(local::__gpGlobal);
 return 0;
}

