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
  //__gpSpdlog = shared::ISpdlog::CreateInterface(
  // shared::Win::GetModuleNameA(true, nullptr),
  // shared::Win::GetModulePathA(nullptr)
  //);

 }

 void Main::UnInit() {
  //shared::ISpdlog::DestoryInterface();
 }



 Main* __gpMain = nullptr;
}///namespace local