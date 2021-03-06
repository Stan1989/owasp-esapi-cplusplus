/*
 * OWASP Enterprise Security API (ESAPI)
 *
 * This file is part of the Open Web Application Security Project (OWASP)
 * Enterprise Security API (ESAPI) project. For details, please see
 * <a href="http://www.owasp.org/index.php/ESAPI">http://www.owasp.org/index.php/ESAPI</a>.
 *
 * Copyright (c) 2011 - The OWASP Foundation
 *
 * @author Kevin Wall, kevin.w.wall@gmail.com
 * @author Jeffrey Walton, noloader@gmail.com
 * @author David Anderson, david.anderson@aspectsecurity.com
 * @author Andrew Durkin, atdurkin@gmail.com
 */

#include "EsapiCommon.h"

#if defined(ESAPI_OS_WINDOWS_STATIC)
// do not enable BOOST_TEST_DYN_LINK
#elif defined(ESAPI_OS_WINDOWS_DYNAMIC)
# define BOOST_TEST_DYN_LINK
#elif defined(ESAPI_OS_WINDOWS)
# error "For Windows, ESAPI_OS_WINDOWS_STATIC or ESAPI_OS_WINDOWS_DYNAMIC must be defined"
#else
# define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "EsapiCommon.h"
using esapi::NarrowString;
using esapi::WideString;

#include "util/SecureArray.h"
using esapi::SecureByteArray;

#include "util/TextConvert.h"
using esapi::TextConvert;

#include "crypto/PlainText.h"
using esapi::PlainText;

BOOST_AUTO_TEST_CASE(VerifyPlainText_1)
{
  // Construction
  PlainText p;
  BOOST_CHECK_MESSAGE(p.length() == 0, "Failed to construct PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_2)
{
  // Copy
  PlainText p;
  PlainText pp(p);
  BOOST_CHECK_MESSAGE(pp.length() == 0, "Failed to construct PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_3)
{
  // Assignment
  PlainText p;
  PlainText pp = p;
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_4)
{
  // Construction
  NarrowString s("a");
  PlainText p(s);
  BOOST_CHECK_MESSAGE(p.length() == 1, "Failed to construct PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_5)
{
  // Construction
  NarrowString s(1, 'a');
  PlainText p(s);
  BOOST_CHECK_MESSAGE(p.length() == 1, "Failed to construct PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_6)
{
  // Copy
  NarrowString s("a");
  PlainText p(s);
  PlainText pp(p);
  BOOST_CHECK_MESSAGE(pp.length() == 1, "Failed to copy PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_7)
{
  // Copy
  NarrowString s(1, 'a');
  PlainText p(s);
  PlainText pp(p);
  BOOST_CHECK_MESSAGE(pp.length() == 1, "Failed to copy PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_8)
{
  // Assignment
  NarrowString s("a");
  PlainText p(s);
  PlainText pp = p;
  BOOST_CHECK_MESSAGE(pp.length() == 1, "Failed to assign PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_9)
{
  // Assignment
  NarrowString s(1, 'a');
  PlainText p(s);
  PlainText pp = p;
  BOOST_CHECK_MESSAGE(pp.length() == 1, "Failed to assign PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_10)
{
  // Construction
  NarrowString s("\u988a");
  PlainText p(s);
  BOOST_CHECK_MESSAGE(p.length() == 3, "Failed to construct PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_11)
{
  // Copy
  NarrowString s("\u988a");
  PlainText p(s);
  PlainText pp(p);
  BOOST_CHECK_MESSAGE(pp.length() == 3, "Failed to copy PlainText");
}

BOOST_AUTO_TEST_CASE(VerifyPlainText_12)
{
  // Assignment
  NarrowString s("\u988a");
  PlainText p(s);
  PlainText pp = p;
  BOOST_CHECK_MESSAGE(pp.length() == 3, "Failed to assign PlainText");
}

/*
BOOST_AUTO_TEST_CASE(VerifyPlainText_13) //:Test assignment and comparison.
{
  WideString wstr1 = L"A\u00ea\u00f1\u00fcC";     //:"AêñüC" // Check me !!!
  WideString wstr2 = TextConvert::NarrowToWide("AêñüC");     //:Same as above.
  PlainText str1(wstr1), str2(wstr2);
  BOOST_CHECK(str1.equals(str1));
  BOOST_CHECK(str1.equals(str2));
  BOOST_CHECK(!str1.toString().empty());
  BOOST_CHECK(str1.toString() == wstr1);
  BOOST_CHECK(str2.toString() == wstr2);
  BOOST_CHECK(str2.toString().length() == wstr2.length());
}
*/

BOOST_AUTO_TEST_CASE(VerifyPlainText_14) //:Test Empty NarrowString.
{
  PlainText pt("");
  BOOST_CHECK(pt.toString() == "");
  BOOST_CHECK(pt.length() == 0);
  SecureByteArray bytes = pt.asBytes();
  BOOST_CHECK(bytes.length() == 0);
}

#if 0
BOOST_AUTO_TEST_CASE(VerifyPlainText_15) //:Test Overwrite
{
 // Under the debugger, the narrow NarrowString is as follows. Its causing failures under ICC.
 // I believe it needs a code page/encoding/locale associated with it (by default, its
 // UTF-8, which may not be correct here).
 // (gdb) p str
 // $4 = (const esapi::NarrowString &) @0x7fffffffc920: {
 // _M_dataplus = { ..., _M_p = 0x6ed168 "A\352\361\374C"}}
  NarrowString unicodeStr = TextConvert::NarrowToWide("A\u00ea\u00f1\u00fcC"); // Check me !!!
  SecureByteArray origBytes = TextConvert::GetBytes(unicodeStr);
  PlainText pt(origBytes);
  BOOST_CHECK(pt.toString() == unicodeStr);
  //BOOST_CHECK(origBytes == pt.asBytes());  //:Can't compare SecureByteArrays with == operator
  size_t origLen = origBytes.length();
  pt.overwrite();
  SecureByteArray overwrittenBytes = pt.asBytes();
  size_t afterLen = overwrittenBytes.length();
  BOOST_CHECK(origLen == afterLen);
  size_t sum = 0;
  for(size_t i = 0; i < afterLen; i++)
    if(overwrittenBytes[i] == '*')  // Check me !!!
      sum++;
  BOOST_CHECK(sum == afterLen);
}
#endif

