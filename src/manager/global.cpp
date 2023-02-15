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

   m_Ready.store(true);
  } while (0);
 }
 void Global::UnInit() {

  m_Ready.store(false);
 }
}///namespace local