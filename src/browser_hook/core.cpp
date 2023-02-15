#include "stdafx.h"

namespace local {

 Core::Core() {
  Init();
 }

 Core::~Core() {
  UnInit();
 }

 void Core::Init() {
  
 }

 void Core::UnInit() {

 }

 bool Core::Open() {
  do {
   if (m_IsOpen.load())
    break;


   m_IsOpen.store(true);
  } while (0);
  return m_IsOpen.load();
 }

 void Core::Close() {
  do {
   if (!m_IsOpen.load())
    break;


   m_IsOpen.store(false);
  } while (0);
 }

}///namespace local