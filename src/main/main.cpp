#include "stdafx.h"

namespace local {

 Main::Main() {
  Init();
 }

 Main::~Main() {
  UnInit();
 }

 void Main::Release() const {
  delete this;
 }

 void Main::Init() {

 }

 void Main::UnInit() {

 }



 Main* __gpMain = nullptr;
}///namespace local