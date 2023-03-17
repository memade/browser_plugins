#if !defined(__65BD1CB5_7E37_4D1E_875A_187F9DD877D2__)
#define __65BD1CB5_7E37_4D1E_875A_187F9DD877D2__

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_iterators.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"

namespace shared {

 using tf_apidxml_char_doc = rapidxml::xml_document<char>;
 using tf_rapidxml_wchar_doc = rapidxml::xml_document<wchar_t>;

 static tf_rapidxml_wchar_doc* rapidxml_parse(const std::wstring& input_data) {
  auto pDoc = new tf_rapidxml_wchar_doc();
  try {
   pDoc->parse<0>((wchar_t*)input_data.c_str());
  }
  catch (rapidxml::parse_error& err) {
   auto what = err.what();
   if (pDoc) {
    delete pDoc;
    pDoc = nullptr;
   }
  }
  return pDoc;
 }

 static tf_apidxml_char_doc* rapidxml_parse(const std::string& input_data) {
  auto pDoc = new tf_apidxml_char_doc();
  try {
   pDoc->parse<0>((char*)input_data.c_str());
  }
  catch (rapidxml::parse_error& err) {
   auto what = err.what();
   if (pDoc) {
    delete pDoc;
    pDoc = nullptr;
   }
  }
  return pDoc;
 }

}///namespace shared

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 01 Mar 2023 22:16:22 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__65BD1CB5_7E37_4D1E_875A_187F9DD877D2__
