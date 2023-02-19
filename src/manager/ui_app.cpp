#include "stdafx.h"

namespace local {

 UIApp::UIApp() {

 }

 UIApp::~UIApp() {

 }

 void UIApp::Init() {
  nbase::ThreadManager::RegisterThread(0);
#ifdef _DEBUG
  // Debug 模式下使用本地文件夹作为资源
  // 默认皮肤使用 resources\\themes\\default
  // 默认语言使用 resources\\lang\\zh_CN
  // 如需修改请指定 Startup 最后两个参数
  ui::GlobalManager::Startup(
#if 0
   theme_dir + L"resources\\",
#else
   LR"(D:\__Github__\Windows\projects\browser_plugins\src\manager\res\skin\)",
#endif
   ui::CreateControlCallback(), false);
#else
  ui::GlobalManager::OpenResZip(MAKEINTRESOURCE(IDR_SKIN), L"ZIP", "");
  ui::GlobalManager::Startup(L"skin\\", ui::CreateControlCallback(), false);
#endif
  ui::GlobalManager::EnableAutomation();
  // 创建一个默认带有阴影的居中窗口
  auto frame = new UIFrame();
  frame->Create(NULL, frame->GetWindowClassName().c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
  frame->CenterWindow();
  frame->ShowWindow();
 }
 void UIApp::Cleanup() {
  ui::GlobalManager::Shutdown();
  SetThreadWasQuitProperly(true);
  nbase::ThreadManager::UnregisterThread();
 }

}///namespace local