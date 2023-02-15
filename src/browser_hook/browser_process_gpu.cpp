#include "stdafx.h"

namespace local {

 BrowserProcessGpu::BrowserProcessGpu() {

 }

 BrowserProcessGpu::~BrowserProcessGpu() {

 }

 void BrowserProcessGpu::Release() const {
  delete this;
 }

 bool BrowserProcessGpu::Start() {
  return false;
 }

 void BrowserProcessGpu::Stop() {

 }

}///namespace local