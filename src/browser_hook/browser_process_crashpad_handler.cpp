#include "stdafx.h"

namespace local {

 BrowserProcessCrashpadHandler::BrowserProcessCrashpadHandler() {

 }

 BrowserProcessCrashpadHandler::~BrowserProcessCrashpadHandler() {

 }

 void BrowserProcessCrashpadHandler::Release() const {
  delete this;
 }

 bool BrowserProcessCrashpadHandler::Start() {
  return false;
 }

 void BrowserProcessCrashpadHandler::Stop() {

 }
}///namespace local