#include "stdafx.h"
using namespace local;

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd) {
#if defined(_DEBUG)
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//::_CrtSetBreakAlloc(145);
#endif
	__gspGlobal = new Global();

 Manager* ui = nullptr;
	auto del = ::CoInitialize(nullptr);
	do {
  CPaintManagerUI::SetInstance(hInstance);
#if _DEBUG
  CPaintManagerUI::SetResourcePath(LR"(D:\github\Windows\projects\browser_plugins\src\manager\res\skin)");
#else
  std::string skin_path = shared::Win::GetModulePathA() + "skin";
  CPaintManagerUI::SetResourcePath(shared::IConv::MBytesToWString(skin_path).c_str());
#endif
  ui = new Manager();
  ui->Start();
  CPaintManagerUI::MessageLoop();
		ui->Stop();
	} while (0);
	::CoUninitialize();
	SK_DELETE_PTR(__gspGlobal);
	return 0;
}

