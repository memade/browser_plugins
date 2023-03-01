#include "stdafx.h"

namespace local {
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 UIUserBrowserConfigListbox::UIUserBrowserConfigListbox() {

 }
 UIUserBrowserConfigListbox::~UIUserBrowserConfigListbox() {

 }
 bool UIUserBrowserConfigListbox::CreateUserBrowserConfigItem(const std::string& json_data) {
  bool result = false;
  do {
   auto item = new UIUserBrowserConfigListItem(json_data);
   if (!AddAt(item, 0))
    break;
   item->UpdateTitle();
   result = true;
  } while (0);
  return result;
 }
 bool UIUserBrowserConfigListbox::RemoveUserBrowserConfigItem() {
  bool result = false;
  do {
   auto sel = GetCurSel();
   if (sel < 0)
    break;
   auto sel_item = (UIUserBrowserConfigListItem*)GetItemAt(sel);
   if (!sel_item)
    break;
   Global::ConfigGet()->PopUserBrowserConfig(sel_item->Identify());
   result = RemoveAt(sel);
  } while (0);
  return result;
 }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 UIUserBrowserConfigListItem::UIUserBrowserConfigListItem(const std::string& json_data) {
  ui::GlobalManager::FillBoxWithCache(this, L"main/listbox_browser_config_item.xml");
  if ((*this << json_data))
   RawData = json_data;
 }
 UIUserBrowserConfigListItem::UIUserBrowserConfigListItem(const std::uint64_t& key) : identify(key) {
  *this >> RawData;
  ui::GlobalManager::FillBoxWithCache(this, L"main/listbox_browser_config_item.xml");
 }

 UIUserBrowserConfigListItem::~UIUserBrowserConfigListItem() {
 }
 void UIUserBrowserConfigListItem::operator>>(UIUserBrowserConfigPage* ui_config_page) const {
  if (ui_config_page)
   *ui_config_page << RawData;
 }
 void UIUserBrowserConfigListItem::operator>>(std::string& output) const {
  output.clear();
  do {
   rapidjson::Document doc{ rapidjson::kObjectType };

   doc.AddMember(
    rapidjson::Value().SetString(SK_VNAME(identify), doc.GetAllocator()).Move(),
    rapidjson::Value().SetUint64(identify).Move(),
    doc.GetAllocator());

   doc.AddMember(
    rapidjson::Value().SetString(SK_VNAME(name), doc.GetAllocator()).Move(),
    rapidjson::Value().SetString("新建配置", doc.GetAllocator()).Move(),
    doc.GetAllocator());

   doc.AddMember(
    rapidjson::Value().SetString(SK_VNAME(comment), doc.GetAllocator()).Move(),
    rapidjson::Value().SetString("", doc.GetAllocator()).Move(),
    doc.GetAllocator());

   doc.AddMember(
    rapidjson::Value().SetString(SK_VNAME(user_data_dir), doc.GetAllocator()).Move(),
    rapidjson::Value().SetString("", doc.GetAllocator()).Move(),
    doc.GetAllocator());

   doc.AddMember(
    rapidjson::Value().SetString(SK_VNAME(proxy_address), doc.GetAllocator()).Move(),
    rapidjson::Value().SetString("", doc.GetAllocator()).Move(),
    doc.GetAllocator());

   doc.AddMember(
    rapidjson::Value().SetString(SK_VNAME(proxy_account), doc.GetAllocator()).Move(),
    rapidjson::Value().SetString("", doc.GetAllocator()).Move(),
    doc.GetAllocator());

   doc.AddMember(
    rapidjson::Value().SetString(SK_VNAME(proxy_password), doc.GetAllocator()).Move(),
    rapidjson::Value().SetString("", doc.GetAllocator()).Move(),
    doc.GetAllocator());

   doc.AddMember(
    rapidjson::Value().SetString(SK_VNAME(proxy_enable), doc.GetAllocator()).Move(),
    rapidjson::Value().SetBool(proxy_enable).Move(),
    doc.GetAllocator());

   doc.AddMember(
    rapidjson::Value().SetString(SK_VNAME(user_agent), doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(user_agent.c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator());

   output = shared::Json::toString(doc);
  } while (0);
 }
 bool UIUserBrowserConfigListItem::operator<<(const std::string& input) {
  bool result = false;
  do {
   if (input.empty())
    break;
   rapidjson::Document doc;
   if (doc.Parse(input.data(), input.size()).HasParseError())
    break;
   if (!doc.IsObject())
    break;
   if (doc.ObjectEmpty())
    break;
   if (!doc.HasMember("identify"))
    break;
   if (!doc["identify"].IsNumber())
    break;
   identify = doc["identify"].GetUint64();
   if (!doc.HasMember("name"))
    break;
   name = doc["name"].GetString();
   if (name.empty())
    break;
   Title = shared::IConv::MBytesToWString(name);
   RawData = input;
   result = true;
  } while (0);
  return result;
 }
 const std::uint64_t& UIUserBrowserConfigListItem::Identify() const {
  return identify;
 }
 void UIUserBrowserConfigListItem::SetTitle(const std::wstring& title) {
  SetText(title);
 }
 std::wstring UIUserBrowserConfigListItem::GetTitle() {
  return GetText();
 }
 void UIUserBrowserConfigListItem::UpdateTitle() {
  SetText(Title);
 }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 UIUserBrowserConfigPage::UIUserBrowserConfigPage() {
  ui::GlobalManager::FillBoxWithCache(this, L"main/listbox_browser_config_page.xml");

 }
 UIUserBrowserConfigPage::~UIUserBrowserConfigPage() {

 }
 void UIUserBrowserConfigPage::Default() {
  SetUserAgentDefault();
 }
 void UIUserBrowserConfigPage::SetTitle(const std::wstring& title) {
  auto ui = (ui::RichEdit*)FindSubControl(L"edit_user_browser_config_page_name");
  if (ui)
   ui->SetText(title);
 }
 std::wstring UIUserBrowserConfigPage::GetTitle() {
  std::wstring result;
  auto ui = (ui::RichEdit*)FindSubControl(L"edit_user_browser_config_page_name");
  if (ui)
   result = ui->GetText();
  return result;
 }
 void UIUserBrowserConfigPage::SetName(const std::wstring& name) {
  auto ui = (ui::RichEdit*)FindSubControl(L"name");
  if (ui)
   ui->SetText(name);
 }
 std::wstring UIUserBrowserConfigPage::GetName() {
  std::wstring result;
  auto ui = (ui::RichEdit*)FindSubControl(L"name");
  if (ui)
   result = ui->GetText();
  return result;
 }
 void UIUserBrowserConfigPage::SetComment(const std::wstring& comment) {
  auto ui = (ui::RichEdit*)FindSubControl(L"comment");
  if (ui)
   ui->SetText(comment);
 }
 std::wstring UIUserBrowserConfigPage::GetComment() {
  std::wstring result;
  auto ui = (ui::RichEdit*)FindSubControl(L"comment");
  if (ui)
   result = ui->GetText();
  return result;
 }
 void UIUserBrowserConfigPage::SetUserAgentDefault() {
  auto ui = (ui::Combo*)FindSubControl(L"user_agent");
  if (!ui)
   return;
  if (ui->GetCount() > 0)
   ui->SelectItem(0);
 }
 void UIUserBrowserConfigPage::SetUserAgent(const std::wstring& user_agent) {
  auto ui = (ui::Combo*)FindSubControl(L"user_agent");
  if (!ui)
   return;
  auto count = ui->GetCount();
  if (count > 0)
   ui->SelectItem(0);
  for (int i = 0; i < count; ++i) {
   auto item = (ui::ListContainerElement*)ui->GetItemAt(i);
   if (!item)
    continue;
   if (item->GetText().find(user_agent) == std::wstring::npos)
    continue;
   ui->SelectItem(i);
   break;
  }
 }
 std::wstring UIUserBrowserConfigPage::GetUserAgent() {
  std::wstring result;
  auto ui = (ui::Combo*)FindSubControl(L"user_agent");
  if (ui && ui->GetCurSel() > 0) {
   result = ui->GetText();
  }
  return result;
 }
 void UIUserBrowserConfigPage::SetScreenResolution(const size_t& value) {
  auto ui = (ui::Combo*)FindSubControl(L"screen_resolution");
  if (!ui)
   return;
  auto count = ui->GetCount();
  if (count > 0)
   ui->SelectItem(0);
  for (int i = 0; i < count; ++i) {
   auto item = (ui::ListContainerElement*)ui->GetItemAt(i);
   if (!item)
    continue;
   auto v = wcstoull(item->GetUserData().c_str(), nullptr, 10);
   if (v != value)
    continue;
   ui->SelectItem(i);
   break;
  }
 }
 size_t UIUserBrowserConfigPage::GetScreenResolution() {
  size_t result = 0;
  auto ui = (ui::Combo*)FindSubControl(L"screen_resolution");
  do {
   auto cursel = ui->GetCurSel();
   if (cursel < 0)
    break;
   auto cursel_item = ui->GetItemAt(cursel);
   result = wcstoull(cursel_item->GetUserData().c_str(), nullptr, 10);
  } while (0);
  return result;
 }
 void UIUserBrowserConfigPage::SetAvailableScreenSize(const size_t& value) {
  auto ui = (ui::Combo*)FindSubControl(L"available_screen_size");
  if (!ui)
   return;
  auto count = ui->GetCount();
  if (count > 0)
   ui->SelectItem(0);
  for (int i = 0; i < count; ++i) {
   auto item = (ui::ListContainerElement*)ui->GetItemAt(i);
   if (!item)
    continue;
   auto v = wcstoull(item->GetUserData().c_str(), nullptr, 10);
   if(v != value)
    continue;
   ui->SelectItem(i);
   break;
  }
 }
 size_t UIUserBrowserConfigPage::GetAvailableScreenSize() {
  size_t result = 0;
  auto ui = (ui::Combo*)FindSubControl(L"available_screen_size");
  do {
   auto cursel = ui->GetCurSel();
   if (cursel < 0)
    break;
   auto cursel_item = ui->GetItemAt(cursel);
   result = wcstoull(cursel_item->GetUserData().c_str(), nullptr, 10);
  } while (0);
  return result;
 }
 void UIUserBrowserConfigPage::SetHardwareConcurency(const size_t& value) {
  auto ui = (ui::Combo*)FindSubControl(L"hardware_concurency");
  if (!ui)
   return;
  auto count = ui->GetCount();
  if (count > 0)
   ui->SelectItem(0);
  for (int i = 0; i < count; ++i) {
   auto item = (ui::ListContainerElement*)ui->GetItemAt(i);
   if (!item)
    continue;
   auto v = wcstoull(item->GetUserData().c_str(), nullptr, 10);
   if (v != value)
    continue;
   ui->SelectItem(i);
   break;
  }
 }
 size_t UIUserBrowserConfigPage::GetHardwareConcurency() {
  size_t result = 0;
  auto ui = (ui::Combo*)FindSubControl(L"hardware_concurency");
  do {
   auto cursel = ui->GetCurSel();
   if (cursel < 0)
    break;
   auto cursel_item = ui->GetItemAt(cursel);
   result = wcstoull(cursel_item->GetUserData().c_str(), nullptr, 10);
  } while (0);
  return result;
 }
 void UIUserBrowserConfigPage::SetPlatform(const std::wstring& value) {
  auto ui = (ui::Combo*)FindSubControl(L"platform");
  if (!ui)
   return;
  auto count = ui->GetCount();
  if (count > 0)
   ui->SelectItem(0);
  for (int i = 0; i < count; ++i) {
   auto item = (ui::ListContainerElement*)ui->GetItemAt(i);
   if (!item)
    continue;
   if (item->GetText().find(value) == std::wstring::npos)
    continue;
   ui->SelectItem(i);
   break;
  }
 }
 std::wstring UIUserBrowserConfigPage::GetPlatform() {
  std::wstring result;
  auto ui = (ui::Combo*)FindSubControl(L"platform");
  if (ui && ui->GetCurSel() > 0) {
   result = ui->GetText();
  }
  return result;
 }


 void UIUserBrowserConfigPage::SetJumpUrl(const std::wstring& url) {
  auto ui = (ui::RichEdit*)FindSubControl(L"jumpurl");
  if (ui)
   ui->SetText(url);
 }
 std::wstring UIUserBrowserConfigPage::GetJumpUrl() {
  std::wstring result;
  auto ui = (ui::RichEdit*)FindSubControl(L"jumpurl");
  if (ui)
   result = ui->GetText();
  return result;
 }

 void UIUserBrowserConfigPage::SetWebGLUnmaskedVendor(const std::wstring& value) {
  auto ui = (ui::Combo*)FindSubControl(L"webgl_unmasked_vendor");
  if (!ui)
   return;
  auto count = ui->GetCount();
  if (count > 0)
   ui->SelectItem(0);
  for (int i = 0; i < count; ++i) {
   auto item = (ui::ListContainerElement*)ui->GetItemAt(i);
   if (!item)
    continue;
   if (item->GetText().find(value) == std::wstring::npos)
    continue;
   ui->SelectItem(i);
   break;
  }
 }
 std::wstring UIUserBrowserConfigPage::GetWebGLUnmaskedVendor() {
  std::wstring result;
  auto ui = (ui::Combo*)FindSubControl(L"webgl_unmasked_vendor");
  if (ui && ui->GetCurSel() > 0) {
   result = ui->GetText();
  }
  return result;
 }
 void UIUserBrowserConfigPage::SetWebGLUnmaskedRenderer(const std::wstring& value) {
  auto ui = (ui::Combo*)FindSubControl(L"webgl_unmasked_renderer");
  if (!ui)
   return;
  auto count = ui->GetCount();
  if (count > 0)
   ui->SelectItem(0);
  for (int i = 0; i < count; ++i) {
   auto item = (ui::ListContainerElement*)ui->GetItemAt(i);
   if (!item)
    continue;
   if (item->GetText().find(value) == std::wstring::npos)
    continue;
   ui->SelectItem(i);
   break;
  }
 }
 std::wstring UIUserBrowserConfigPage::GetWebGLUnmaskedRenderer() {
  std::wstring result;
  auto ui = (ui::Combo*)FindSubControl(L"webgl_unmasked_renderer");
  if (ui && ui->GetCurSel() > 0) {
   result = ui->GetText();
  }
  return result;
 }
 void UIUserBrowserConfigPage::SetWebGLVersion(const std::wstring& value) {
  auto ui = (ui::Combo*)FindSubControl(L"webgl_version");
  if (!ui)
   return;
  auto count = ui->GetCount();
  if (count > 0)
   ui->SelectItem(0);
  for (int i = 0; i < count; ++i) {
   auto item = (ui::ListContainerElement*)ui->GetItemAt(i);
   if (!item)
    continue;
   if (item->GetText().find(value) == std::wstring::npos)
    continue;
   ui->SelectItem(i);
   break;
  }
 }
 std::wstring UIUserBrowserConfigPage::GetWebGLVersion() {
  std::wstring result;
  auto ui = (ui::Combo*)FindSubControl(L"webgl_version");
  if (ui && ui->GetCurSel() > 0) {
   result = ui->GetText();
  }
  return result;
 }



 void UIUserBrowserConfigPage::SetIdentify(const std::uint64_t& identify) {
  auto ui = (ui::Label*)FindSubControl(L"identify");
  if (ui)
   ui->SetText(std::to_wstring(identify));
 }
 std::uint64_t UIUserBrowserConfigPage::GetIdentify() {
  std::uint64_t result = 0;
  auto ui = (ui::Label*)FindSubControl(L"identify");
  if (ui)
   result = _tcstoull(ui->GetText().c_str(), nullptr, 10);
  return result;
 }
 void UIUserBrowserConfigPage::ProxyCtrlEnable(const bool& enable) {
  auto ctrl_proxy_address = FindSubControl(L"proxy_address");
  if (ctrl_proxy_address)
   ctrl_proxy_address->SetEnabled(enable);
  auto ctrl_proxy_account = FindSubControl(L"proxy_account");
  if (ctrl_proxy_account)
   ctrl_proxy_account->SetEnabled(enable);
  auto ctrl_proxy_password = FindSubControl(L"proxy_password");
  if (ctrl_proxy_password)
   ctrl_proxy_password->SetEnabled(enable);
 }
 void UIUserBrowserConfigPage::SetProxyEnable(const bool& enable) {
  auto ui = (ui::CheckBox*)FindSubControl(L"proxy_enable");
  if (ui)
   ui->Selected(enable);
  ProxyCtrlEnable(enable);
 }
 bool UIUserBrowserConfigPage::GetProxyEnable() {
  bool result = false;
  auto ui = (ui::CheckBox*)FindSubControl(L"proxy_enable");
  if (ui)
   result = ui->IsSelected();
  return result;
 }
 void UIUserBrowserConfigPage::SetProxyAddress(const std::wstring& address) {
  auto ui = (ui::RichEdit*)FindSubControl(L"proxy_address");
  if (ui)
   ui->SetText(address);
 }
 std::wstring UIUserBrowserConfigPage::GetProxyAddress() {
  std::wstring result;
  auto ui = (ui::RichEdit*)FindSubControl(L"proxy_address");
  if (ui)
   result = ui->GetText();
  return result;
 }
 void UIUserBrowserConfigPage::SetProxyAccount(const std::wstring& account) {
  auto ui = (ui::RichEdit*)FindSubControl(L"proxy_account");
  if (ui)
   ui->SetText(account);
 }
 std::wstring UIUserBrowserConfigPage::GetProxyAccount() {
  std::wstring result;
  auto ui = (ui::RichEdit*)FindSubControl(L"proxy_account");
  if (ui)
   result = ui->GetText();
  return result;
 }
 void UIUserBrowserConfigPage::SetProxyPassword(const std::wstring& password) {
  auto ui = (ui::RichEdit*)FindSubControl(L"proxy_password");
  if (ui)
   ui->SetText(password);
 }
 std::wstring UIUserBrowserConfigPage::GetProxyPassword() {
  std::wstring result;
  auto ui = (ui::RichEdit*)FindSubControl(L"proxy_password");
  if (ui)
   result = ui->GetText();
  return result;
 }
 void UIUserBrowserConfigPage::GenerateDefaultConfig(std::string& output, const std::uint64_t& identify /*= 0*/) {
  output.clear();
  do {
   auto _identify = identify;
   if (_identify <= 0)
    _identify = shared::Win::Time::TimeStamp<std::chrono::microseconds>();
   rapidjson::Document doc{ rapidjson::kObjectType };
   doc.AddMember(
    rapidjson::Value().SetString("identify", doc.GetAllocator()).Move(),
    rapidjson::Value().SetUint64(_identify).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("name", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetName()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("comment", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetComment()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("jumpurl", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetJumpUrl()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );
   
   doc.AddMember(
    rapidjson::Value().SetString("proxy_address", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetProxyAddress()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("proxy_account", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetProxyAccount()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("proxy_password", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetProxyPassword()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("proxy_enable", doc.GetAllocator()).Move(),
    rapidjson::Value().SetBool(GetProxyEnable()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("user_agent", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetUserAgent()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("screen_resolution", doc.GetAllocator()).Move(),
    rapidjson::Value().SetUint64(GetScreenResolution()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("available_screen_size", doc.GetAllocator()).Move(),
    rapidjson::Value().SetUint64(GetAvailableScreenSize()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("hardware_concurency", doc.GetAllocator()).Move(),
    rapidjson::Value().SetUint64(GetHardwareConcurency()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("platform", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetPlatform()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("webgl_unmasked_vendor", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetWebGLUnmaskedVendor()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("webgl_unmasked_renderer", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetWebGLUnmaskedRenderer()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );

   doc.AddMember(
    rapidjson::Value().SetString("webgl_version", doc.GetAllocator()).Move(),
    rapidjson::Value().SetString(shared::IConv::WStringToMBytes(GetWebGLVersion()).c_str(), doc.GetAllocator()).Move(),
    doc.GetAllocator()
   );


   output = shared::Json::toString(doc);
  } while (0);
 }
 std::string UIUserBrowserConfigPage::OutputConfig(const std::uint64_t& identify) {
  std::string result;
  do {
   if (identify <= 0)
    break;
   GenerateDefaultConfig(result, identify);
  } while (0);
  return result;
 }
 bool UIUserBrowserConfigPage::operator<<(const std::string& json_data) {
  bool result = false;
  do {
   if (json_data.empty())
    break;
   rapidjson::Document doc;
   if (doc.Parse(json_data.data(), json_data.size()).HasParseError())
    break;
   if (!doc.IsObject())
    break;
   if (doc.ObjectEmpty())
    break;
   if (doc.HasMember("name") && doc["name"].IsString())
    SetName(shared::IConv::MBytesToWString(doc["name"].GetString()));
   if (doc.HasMember("identify") && doc["identify"].IsNumber())
    SetIdentify(doc["identify"].GetUint64());
   if (doc.HasMember("proxy_enable") && doc["proxy_enable"].IsBool())
    SetProxyEnable(doc["proxy_enable"].GetBool());
   if (doc.HasMember("comment") && doc["comment"].IsString())
    SetComment(shared::IConv::MBytesToWString(doc["comment"].GetString()));
   if (doc.HasMember("jumpurl") && doc["jumpurl"].IsString())
    SetJumpUrl(shared::IConv::MBytesToWString(doc["jumpurl"].GetString()));
   if (doc.HasMember("proxy_address") && doc["proxy_address"].IsString())
    SetProxyAddress(shared::IConv::MBytesToWString(doc["proxy_address"].GetString()));
   if (doc.HasMember("proxy_account") && doc["proxy_account"].IsString())
    SetProxyAccount(shared::IConv::MBytesToWString(doc["proxy_account"].GetString()));
   if (doc.HasMember("proxy_password") && doc["proxy_password"].IsString())
    SetProxyPassword(shared::IConv::MBytesToWString(doc["proxy_password"].GetString()));
   if (doc.HasMember("user_agent") && doc["user_agent"].IsString())
    SetUserAgent(shared::IConv::MBytesToWString(doc["user_agent"].GetString()));

   if (doc.HasMember("screen_resolution") && doc["screen_resolution"].IsNumber())
    SetScreenResolution(doc["screen_resolution"].GetUint64());
   if (doc.HasMember("available_screen_size") && doc["available_screen_size"].IsNumber())
    SetAvailableScreenSize(doc["available_screen_size"].GetUint64());
   if (doc.HasMember("hardware_concurency") && doc["hardware_concurency"].IsNumber())
    SetHardwareConcurency(doc["hardware_concurency"].GetUint64());
   if (doc.HasMember("platform") && doc["platform"].IsString())
    SetPlatform(shared::IConv::MBytesToWString(doc["platform"].GetString()));
   if (doc.HasMember("webgl_unmasked_vendor") && doc["webgl_unmasked_vendor"].IsString())
    SetWebGLUnmaskedVendor(shared::IConv::MBytesToWString(doc["webgl_unmasked_vendor"].GetString()));
   if (doc.HasMember("webgl_unmasked_renderer") && doc["webgl_unmasked_renderer"].IsString())
    SetWebGLUnmaskedRenderer(shared::IConv::MBytesToWString(doc["webgl_unmasked_renderer"].GetString()));
   if (doc.HasMember("webgl_version") && doc["webgl_version"].IsString())
    SetWebGLVersion(shared::IConv::MBytesToWString(doc["webgl_version"].GetString()));

   result = true;
  } while (0);
  return result;
 }
 bool UIUserBrowserConfigPage::operator<<(UIUserBrowserConfigListItem* sel_item) {
  bool result = false;
  do {
   if (!sel_item)
    break;
   Default();
   std::string json_data;
   *sel_item >> json_data;
   if (!(*this << json_data))
    break;
   SetName(sel_item->GetTitle());
   SetIdentify(sel_item->Identify());
   result = true;
  } while (0);
  return result;
 }

}///namespace local