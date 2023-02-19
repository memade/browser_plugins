#include "stdafx.h"

namespace local {
 Global* __gspGlobal = nullptr;
 Global* GlobalGet() { return __gspGlobal; }

 Global::Global() {
  Init();
 }

 Global::~Global() {
  UnInit();
 }
 bool Global::Ready() {
  bool result = false;
  do {
   if (!__gspGlobal)
    break;
   result = __gspGlobal->m_Ready.load();
  } while (0);
  return result;
 }
 void Global::Init() {
  m_Ready.store(false);
  do {
   m_pConfig = new Config();
   //m_pManagerUI = new Manager();
   m_Ready.store(true);
  } while (0);
 }
 void Global::UnInit() {
  //SK_DELETE_PTR(m_pManagerUI);
  SK_DELETE_PTR(m_pConfig);
  m_Ready.store(false);
 }

 Config* Global::ConfigGet() {
  if (__gspGlobal)
   return __gspGlobal->m_pConfig;
  return nullptr;
 }
#if 0
 Manager* Global::MainUI() {
  if (__gspGlobal)
   return __gspGlobal->m_pManagerUI;
  return nullptr;
 }
#endif
}///namespace local