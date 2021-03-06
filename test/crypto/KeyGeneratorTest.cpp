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
using esapi::String;

#include <crypto/Key.h>
#include <crypto/SecretKey.h>
#include <crypto/KeyGenerator.h>
using esapi::Key;
using esapi::SecretKey;
using esapi::KeyGenerator;

#include "util/TextConvert.h"
using esapi::TextConvert;

static const unsigned int KEY_SIZES[] = { 1, 7, 8, 9, 63, 64, 65, 80, 112, 128, 192, 256, 384, 512 };

// Block ciphers
void VerifyAesKeyGenerator();
void VerifyDesEdeKeyGenerator();
void VerifyBlowfishKeyGenerator();
void VerifyCamelliaKeyGenerator();

// HMACs
void VerifyHmacShaKeyGenerator();
void VerifyHmacWhirlpoolKeyGenerator();

void VerifyKey(KeyGenerator& kgen, size_t bytes);
void VerifyKeyGeneration(KeyGenerator&, size_t);

BOOST_AUTO_TEST_CASE( VerifyKeyGenerator )
{
  BOOST_MESSAGE( "Verifying KeyGeneration class" );

  //VerifyAesKeyGenerator();
  //VerifyDesEdeKeyGenerator();
  //VerifyBlowfishKeyGenerator();
  //VerifyCamelliaKeyGenerator();

  VerifyHmacShaKeyGenerator();
  VerifyHmacWhirlpoolKeyGenerator();
}

/**
 * The following Java program prints 3 sizes without excpetions.
 *
 *  Cipher cipher = Cipher.getInstance("AES");
 *  KeyGenerator generator = KeyGenerator.getInstance("AES");
 *  
 *  generator.init(128);
 *  Key key1 = generator.generateKey();
 *  System.out.println("Key 1 size: " + key1.getEncoded().length);
 *  
 *  Key key2 = generator.generateKey();
 *  System.out.println("Key 2 size: " + key2.getEncoded().length);
 *  
 *  generator.init(256);
 *  Key key3 = generator.generateKey();
 *  System.out.println("Key 3 size: " + key3.getEncoded().length);
 */

void VerifyKeyGeneration(KeyGenerator& kgen, size_t bytes)
{
  // #define DUMP_KEYS 1

  // First key generation
  SecretKey k1 = kgen.generateKey();
  BOOST_CHECK_MESSAGE( !(k1.getEncoded().length() < bytes), "Key 1 is too small: " << k1 );

  // Second key generation
  SecretKey k2 = kgen.generateKey();
  BOOST_CHECK_MESSAGE( !(k2.getEncoded().length() < bytes), "Key 2 is too small: " << k2 );

#if defined(DUMP_KEYS)
  BOOST_MESSAGE( "  " << k1 );
#endif

  // Ignore it when single bytes are produced consecutively
  // (fails on occasion for 1 and 2 byte keys).
  BOOST_CHECK_MESSAGE( !(k1 == k2 && k1.getEncoded().length() > 2), "Key 2 is too small: " << k2 );

#if defined(DUMP_KEYS)
  BOOST_MESSAGE( "  " << k2 );
#endif

  // Re-init

  bool success = false;
  try
    {      
      kgen.init((unsigned int)((bytes * 3 / 2) * 8));
      success = true;
    }
  catch(...)
    {      
    }

  BOOST_CHECK_MESSAGE( success, "Failed to re-init() KeyGenerator" );

  try
    {    
      success = false;

      // Third key generation
      SecretKey k3 = kgen.generateKey();
      success = true;
    }
  catch(...)
    {      
    }

  BOOST_CHECK_MESSAGE( success, "Failed to generate key after re-init()" );

  // Test base class reference
  Key& kk = k1;
  kk = k2;
}

void VerifyAesKeyGenerator()
{
  BOOST_MESSAGE( " Verifying AES" );

  String alg;

  ///////////////////////////////////////////////////////////////////////

  alg = "aes";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }
    
  ///////////////////////////////////////////////////////////////////////

  alg = "aes/CBC";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "aes\\cfb";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "aes/OFB";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "aes/OFB/PKCS5";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }
}

void VerifyCamelliaKeyGenerator()
{
  BOOST_MESSAGE( " Verifying Camellia" );

  String alg;

  ///////////////////////////////////////////////////////////////////////

  alg = "CameLLia";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "CameLLia/CBC";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "CameLLia\\cfb";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "CameLLia/OFB";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "CameLLia/OFB/  PKCS5   ";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }
}

void VerifyDesEdeKeyGenerator()
{
  BOOST_MESSAGE( " Verifying DES EDE" );

  String alg;

  ///////////////////////////////////////////////////////////////////////

  alg = "DeSEdE";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "DeSEdE/CBC";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "DeSEdE\\cfb";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "DeSEdE/OFB";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "DeSEdE/OFB\\PKCS 7";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }
}

void VerifyBlowfishKeyGenerator()
{
  BOOST_MESSAGE( " Verifying Blowfish" );

  String alg;

  ///////////////////////////////////////////////////////////////////////

  alg = "BlowFISH";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "BlowFISH/CBC";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "BlowFISH\\cfb";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "BlowFISH/OFB";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "BlowFISH/OFB//Zero";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }
}

void VerifyHmacShaKeyGenerator()
{
  BOOST_MESSAGE( " Verifying HMAC-SHA" );

  String alg;

  ///////////////////////////////////////////////////////////////////////

  alg = "HmacSHA1";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "HmacSHA224";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "HmacSHA256";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "HmacSHA384";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }

  ///////////////////////////////////////////////////////////////////////

  alg = "HmacSHA512";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }
}

void VerifyHmacWhirlpoolKeyGenerator()
{
  BOOST_MESSAGE( " Verifying HMAC-Whirlpoo" );

  String alg = "HmacWhirlpoo";

  for(size_t i = 0; i < COUNTOF(KEY_SIZES); i++)
    {
      KeyGenerator kg(KeyGenerator::getInstance(alg));

      const unsigned int bits = KEY_SIZES[i];
      const unsigned int bytes = (bits+7)/8;
      kg.init(bits);

      BOOST_MESSAGE( "Testing " << kg.getAlgorithm() << " (" << bits << ")" );
      VerifyKeyGeneration(kg, bytes);
    }
}
