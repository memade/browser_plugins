#include "stdafx.h"

namespace local {

 Config::Config() {

 }

 Config::~Config() {

 }

 void Config::Release() const {
  delete this;
 }

}///namespace local