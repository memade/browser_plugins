#include "stdafx.h"

namespace local {

 BrowserProcessUtility::BrowserProcessUtility() {

 }

 BrowserProcessUtility::~BrowserProcessUtility() {

 }

 void BrowserProcessUtility::Release() const {
  delete this;
 }

 bool BrowserProcessUtility::Start() {
  return false;
 }

 void BrowserProcessUtility::Stop() {

 }


}///namespace local