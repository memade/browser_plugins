#include "stdafx.h"

namespace local {
 Config::Config() {

 }
 Config::~Config() {

 }
 void Config::Init() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_ConfigureCacheIntervalMS = Global::SetupGet()->ConfigureCacheIntervalMSGet();
  do {//!@ 用户浏览器配置
   m_UserBrowserConfigPathname = Global::SetupGet()->ProjectConfigPathGet() + "\\config.json";
   if (!shared::Win::AccessA(m_UserBrowserConfigPathname))
    break;
   auto buffer = shared::Win::File::Read(m_UserBrowserConfigPathname);
   if (buffer.empty())
    break;

   rapidjson::Document doc;
   if (doc.Parse(buffer.data(), buffer.size()).HasParseError())
    break;
   if (doc.IsArray()) {
    for (auto it = doc.Begin(); it != doc.End(); ++it) {
     do {
      if (!it->IsObject())
       break;
      if (!it->HasMember("identify"))
       break;
      if (!(*it)["identify"].IsNumber())
       break;
      m_UserBrowserConfigDatas.push((*it)["identify"].GetUint64(), shared::Json::toString(*it));
     } while (0);
    }
   }


  } while (0);

  m_IsOpen.store(true);
  m_Threads.emplace_back([this]() {Process(); });
 }
 void Config::UnInit() {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_IsOpen.store(false);
  for (auto& t : m_Threads)
   t.join();
  m_Threads.clear();
 }
 std::vector<std::string> Config::UserBrowserConfigsSnapshoot() const {
  std::vector<std::string> result;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_UserBrowserConfigDatas.iterate(
   [&](const auto&, auto& node, auto&) {
    result.emplace_back(node);
   });
  return result;
 }
 bool Config::UserBrowserConfigEmpty() const {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   result = m_UserBrowserConfigDatas.empty();
  } while (0);
  return result;
 }
 std::string Config::GetUserBrowserConfig(const std::uint64_t& identify) const {
  std::string result;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_UserBrowserConfigDatas.search(identify,
   [&](const auto& found) {
    result = found;
   });
  return result;
 }
 void Config::PopUserBrowserConfig(const std::uint64_t& identify) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  if (m_UserBrowserConfigDatas.pop(identify, [](const auto&, auto&) {}))
   m_NotifyFlag.store(true);
 }
 bool Config::PushUserBrowserConfig(const std::string& json_node) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  do {
   if (json_node.empty())
    break;
   rapidjson::Document doc;
   if (doc.Parse(json_node.data(), json_node.size()).HasParseError())
    break;
   if (!doc.HasMember("identify"))
    break;
   if (!doc["identify"].IsNumber())
    break;
   m_UserBrowserConfigDatas.push(doc["identify"].GetUint64(), shared::Json::toString(doc));
   m_NotifyFlag.store(true);
   result = true;
  } while (0);
  return result;
 }







 void Config::Process() {
  do {
   do {
    if (!m_NotifyFlag.load())
     break;
    shared::Win::File::Empty(m_UserBrowserConfigPathname);
    std::string write_cache;
    m_UserBrowserConfigDatas.iterate(
     [&](const auto& key, auto& val, auto& itbreak, auto&) {
      write_cache.append(val).append(",");
     });
    if (!write_cache.empty()) {
     write_cache.pop_back();
     write_cache.insert(0, "[");
     write_cache.push_back(']');
     shared::Win::File::Write(m_UserBrowserConfigPathname, write_cache);
    }
    m_NotifyFlag.store(false);
   } while (0);

   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   if (!m_IsOpen.load())
    break;
  } while (1);
 }
}///namespace local