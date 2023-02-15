#include "stdafx.h"
#if 0
int main(int argc, char** argv) {
#if defined(_DEBUG)
 ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 //::_CrtSetBreakAlloc(3709);
#endif

 local::__gspGlobal = new local::Global();
 if (!local::Global::Ready()) {
  return -1;  
 }


 shared::Win::MainProcess(
  [&](const std::string& input, bool& exit) {
   if (input == "q") {
    exit = true;
   }
   else if (input == "test") {

   }
  });

 SK_DELETE_PTR(local::__gspGlobal);
 return 0;
}
#endif


