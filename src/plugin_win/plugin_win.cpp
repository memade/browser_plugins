#include "stdafx.h"

namespace local {

 Plugin::Plugin() {
  Init();
 }

 Plugin::~Plugin() {
  UnInit();
 }

 void Plugin::Release() const {
  delete this;
 }

 void Plugin::Init() {
  m_pConfig = new Config();
 }

 void Plugin::UnInit() {
  m_pConfig->Release();
 }

 IConfig* Plugin::ConfigGet() const {
  return m_pConfig;
 }

 bool Plugin::Start() {
  return false;
 }

 void Plugin::Stop() {

 }

 void Plugin::EnumPluginPath(const char* folder_path, const std::function<void(const char*)>& found_s) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (!found_s || !folder_path)
    break;
   if (!shared::Win::AccessA(folder_path))
    break;
   tfEnumFolderNode folder_s;
   tfEnumFolderNode file_s;
   shared::Win::EnumFolder(folder_path, folder_s, file_s, "*.dll", false, nullptr);
   if (file_s.empty())
    break;
   for (const auto& file : file_s)
    found_s(file.second.c_str());  
  } while (0);
 }




 Plugin* __gpPlugin = nullptr;
}///namespace local