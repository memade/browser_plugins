#include "stdafx.h"

namespace local {
 Global::Global() {
  Init();
 }

 Global::~Global() {
  UnInit();
 }
 bool Global::Ready() {
  bool result = false;
  do {
   if (!__gpGlobal)
    break;
   result = __gpGlobal->m_Ready.load();
  } while (0);
  return result;
 }
 void Global::Init() {
  m_Ready.store(false);
  do {
   m_pSetup = new Setup();
   if (!m_pSetup->Init())
    break;
   m_pConfig = new Config();
   m_Ready.store(true);
  } while (0);
 }
 void Global::UnInit() {
  if (m_pConfig)
   m_pConfig->UnInit();
  if (m_pSetup)
   m_pSetup->UnInit();

  SK_DELETE_PTR(m_pSetup);
  SK_DELETE_PTR(m_pConfig);
  m_Ready.store(false);
 }

 Config* Global::ConfigGet() {
  if (__gpGlobal)
   return __gpGlobal->m_pConfig;
  return nullptr;
 }
 Setup* Global::SetupGet() {
  if (__gpGlobal)
   return __gpGlobal->m_pSetup;
  return nullptr;
 }
#if 0
 Manager* Global::MainUI() {
  if (__gspGlobal)
   return __gspGlobal->m_pManagerUI;
  return nullptr;
 }
#endif



 Global* __gpGlobal = nullptr;
 HINSTANCE __gpHinstance = nullptr;
 Global* GlobalGet() { return __gpGlobal; }
}///namespace local