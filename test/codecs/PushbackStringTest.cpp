/*
 * OWASP Enterprise Security API (ESAPI)
 *
 * This file is part of the Open Web Application Security Project (OWASP)
 * Enterprise Security API (ESAPI) project. For details, please see
 * <a href="http://www.owasp.org/index.php/ESAPI">http://www.owasp.org/index.php/ESAPI</a>.
 *
 * Copyright (c) 2011 - The OWASP Foundation
 *
 * @author Dan Amodio, dan.amodio@aspectsecurity.com
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

#include "EsapiCommon.h"
using esapi::Char;
using esapi::String;

#include "codecs/PushbackString.h"
using esapi::PushbackString;

#if !defined(ESAPI_BUILD_RELEASE)
BOOST_AUTO_TEST_CASE( PushbackStringHasNext )
{
  PushbackString pbs("asdf");

  BOOST_CHECK(pbs.index() == 0);
  BOOST_CHECK(pbs.input.compare("asdf") == 0);
  BOOST_CHECK(pbs.hasNext());

  pbs.input = "";
  BOOST_CHECK(pbs.hasNext() == false);
}
#endif

BOOST_AUTO_TEST_CASE( PushbackStringNext )
{
  PushbackString pbs("asdf");

  Char next = pbs.next();

  BOOST_CHECK_MESSAGE(next == 'a', "On string 'asdf' next() returned '" << next << "'");
  BOOST_CHECK(next != 0);

  pbs.pushback('x');
  next = pbs.next();
  BOOST_CHECK(next != 0);
  BOOST_CHECK(next != 'a');
  BOOST_CHECK(next == 'x');

  next = pbs.next();
  BOOST_CHECK(next == 's');

  next = pbs.next();
  BOOST_CHECK(next == 'd');

  next = pbs.next();
  BOOST_CHECK(next == 'f');

  next = pbs.next();
  BOOST_CHECK(next == 0);

  next = pbs.next();
  BOOST_CHECK(next == 0);

}

BOOST_AUTO_TEST_CASE( PushbackStringIsHexDigit )
{
  PushbackString pbs("asdf");

  BOOST_CHECK(pbs.isHexDigit('a'));
  BOOST_CHECK(pbs.isHexDigit('f'));
  BOOST_CHECK(pbs.isHexDigit('3'));
  BOOST_CHECK(pbs.isHexDigit('E'));
  BOOST_CHECK(!pbs.isHexDigit((char)0x00));
  BOOST_CHECK(!pbs.isHexDigit('P'));
  BOOST_CHECK(!pbs.isHexDigit('#'));
}

BOOST_AUTO_TEST_CASE( PushbackStringIsOctalDigit )
{
  PushbackString pbs("asdf");

  BOOST_CHECK(pbs.isOctalDigit('1'));
  BOOST_CHECK(pbs.isOctalDigit('7'));
  BOOST_CHECK(!pbs.isOctalDigit('9'));
  BOOST_CHECK(!pbs.isOctalDigit('b'));
}

BOOST_AUTO_TEST_CASE( PushbackStringNextHex )
{
  PushbackString pbs("asdf");

  Char next = pbs.nextHex();
  BOOST_CHECK(next == 0x61);
  BOOST_CHECK(next == 'a');
  BOOST_CHECK(next != 0);

  next = pbs.nextHex();

  // s is not hex
  BOOST_CHECK(next == 0);
}

#if !defined(ESAPI_BUILD_RELEASE)
BOOST_AUTO_TEST_CASE( PushbackStringNextOctal )
{
  PushbackString pbs("141");

  Char next = pbs.nextOctal();
  BOOST_CHECK_MESSAGE(next == '1', "nextOctal() on 'asdf' returned '" << next << "'");
  BOOST_CHECK(next != 0);

  pbs.input = "9999";
  next = pbs.nextOctal();
  BOOST_CHECK(next == 0);
}
#endif

BOOST_AUTO_TEST_CASE( PushbackStringTest2 )
{
  PushbackString pbs("asdf");

  BOOST_CHECK(true);
}

