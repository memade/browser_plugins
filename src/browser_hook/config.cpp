#include "stdafx.h"

namespace local {
 Config::Config() {

 }
 Config::~Config() {

 }
 void Config::Release() const {
  delete this;
 }
 void Config::operator>>(std::string& output) const {
  output.clear();
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  std::ostringstream os;
  //!@ Begin
  os << R"(<?xml version="1.0" encoding="UTF-8" ?>)" << std::endl;
  os << R"(<Config>)" << std::endl;

  //!@ Global
  //! 
  //! 
  os << R"(<Global)" << std::endl;
  os << R"(MainSwitch=)" << (m_MainSwitch ? "true" : "false") << std::endl;

  os << R"(>)" << std::endl;
  //!@ Hookup
  //! 
  //! 
  os << R"(<Hookup)" << std::endl;
  os << R"(GetNativeSystemInfo=)" << (m_Hookup_GetNativeSystemInfo ? "true" : "false") << std::endl;


  os << R"(>)" << std::endl;

  //!@ End
  os << R"(</Config>)" << std::endl;
 
  output = os.str();
 }
 bool Config::operator<<(const std::string& input) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  auto xmldoc = std::make_shared<rapidxml::xml_document<>>();
  std::string cache = input;
  do {
   if (cache.empty())
    break;
   try {
    xmldoc->parse<0>(cache.data());
   }
   catch (rapidxml::parse_error& err) {
    auto what = err.what();
    break;
   }
   auto setup = xmldoc->first_node("Config");
   if (!setup)
    break;

   auto first_node = setup->first_node();
   while (first_node) {
    if (!strcmp("Global", first_node->name())) {
     auto first_attribute = first_node->first_attribute();
     while (first_attribute) {
      if (!strcmp("MainSwitch", first_attribute->name())) {
       m_MainSwitch = false;
       if (!strcmp(first_attribute->value(), "true"))
        m_MainSwitch = true;
      }
      first_attribute = first_attribute->next_attribute();
     }
    }
    else if (!strcmp("Hookup", first_node->name())) {
     auto first_attribute = first_node->first_attribute();
     while (first_attribute) {
      if (!strcmp("GetNativeSystemInfo", first_attribute->name())) {
       m_Hookup_GetNativeSystemInfo = false;
       if (!strcmp(first_attribute->value(), "true"))
        m_Hookup_GetNativeSystemInfo = true;
      }
      first_attribute = first_attribute->next_attribute();
     }
    }
    first_node = first_node->next_sibling();
   }
   result = true;
 }while (0);
 return result;
}
 const bool& Config::MainSwitch() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_MainSwitch;
 }
 void Config::MainSwitch(const bool& enable) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_MainSwitch = enable;
 }
 const bool& Config::Hookup_GetNativeSystemInfo() const {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  return m_Hookup_GetNativeSystemInfo;
 }
 void Config::Hookup_GetNativeSystemInfo(const bool& enable) {
  std::lock_guard<std::mutex> lock{ *m_Mutex };
  m_Hookup_GetNativeSystemInfo = enable;
 }
}///namespace local