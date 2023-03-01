#include "stdafx.h"
#include "export.h"
using namespace local;

static const char exports_common_functions[][260] = {
 "EnumPluginFolder",
};

__shared_api_ void __stdcall api_object_init(void** route, size_t& route_size) {
 do {
  std::string sfuns;
  const size_t function_count = sizeof(exports_common_functions) / sizeof(exports_common_functions[0]);
  for (size_t i = 0; i < function_count; ++i) {
   if (::strlen(exports_common_functions[i]) <= 0)
    continue;
   sfuns.append(exports_common_functions[i]).append(",");
  }
  if (sfuns.empty())
   break;
  sfuns.pop_back();
  route_size = sfuns.size();
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, sfuns.data(), route_size);
 } while (0);
}

__shared_api_ void __stdcall api_object_uninit() {

}

__shared_api_ bool __stdcall EnumPluginFolder(void** route, size_t& route_size, const void* folder_path) {
 bool result = false;
 do {
  if (!folder_path)
   break;
  const char* path = reinterpret_cast<const char*>(folder_path);
  if (!shared::Win::AccessA(path))
   break;
  tfEnumFolderNode folder_s;
  tfEnumFolderNode file_s;
  shared::Win::EnumFolder(path, folder_s, file_s, "*.dll", false, nullptr);
  if (file_s.empty())
   break;
  std::string all_files;
  for (const auto& file : file_s)
   all_files.append(file.second).append(",");
  all_files.pop_back();
  route_size = all_files.size();
  *route = HeapAlloc(GetProcessHeap(), 0, route_size);
  memcpy(*route, all_files.data(), route_size);
  result = true;
 } while (0);
 return result;
}
