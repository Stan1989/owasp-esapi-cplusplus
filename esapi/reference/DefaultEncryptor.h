/**
* OWASP Enterprise Security API (ESAPI)
*
* This file is part of the Open Web Application Security Project (OWASP)
* Enterprise Security API (ESAPI) project. For details, please see
* http://www.owasp.org/index.php/ESAPI.
*
* Copyright (c) 2011 - The OWASP Foundation
*/

#pragma once

#include "Encryptor.h"

#include "crypto/PlainText.h"
#include "crypto/CipherText.h"
#include "crypto/SecretKey.h"
#include "crypto/MessageDigest.h"
#include "crypto/Crypto++Common.h"
#include "errors/EncryptionException.h"
#include "errors/InvalidArgumentException.h"

#include <string>
#include <cstdio>

// Must be consistent with JavaEncryptor.java.
// http://owasp-esapi-java.googlecode.com/svn/trunk/src/main/java/org/owasp/esapi/reference/crypto/JavaEncryptor.java

namespace esapi
{
  class ESAPI_EXPORT DefaultEncryptor : public Encryptor
  {
  public:

    static std::string DefaultDigestAlgorithm;
    static unsigned int DefaultDigestIterations;

  public:

    virtual std::string hash(const std::string &plaintext, const std::string &salt, unsigned int iterations = DefaultDigestIterations) throw (EncryptionException);

    virtual CipherText encrypt(const PlainText& plainText) throw (EncryptionException)
    {
      return CipherText();
    }

    virtual CipherText encrypt(const SecretKey& secretKey, const PlainText& plainText) throw (EncryptionException)
    {
      return CipherText();
    }

    virtual PlainText decrypt(const CipherText& cipherText) throw (EncryptionException)
    {
      return PlainText();
    }

    virtual PlainText decrypt(const SecretKey& secretKey, const CipherText& cipherText) throw (EncryptionException)
    {
      return PlainText();
    }

    virtual std::string sign(const std::string & message) throw (EncryptionException)
    {
      return std::string();
    }

    virtual bool verifySignature(const std::string &, const std::string &)
    {
      return false;
    }

    virtual std::string seal(const std::string &, long) throw (IntegrityException)
    {
      return std::string();
    }

    virtual std::string unseal(const std::string &) throw (EncryptionException)
    {
      return std::string();
    }

    virtual bool verifySeal(const std::string &)
    {
      return false;
    }

    virtual long getRelativeTimeStamp(long timeStamp)
    {
      return 0;
    }

    virtual long getTimeStamp()
    {
      return 0;
    }

    // CTORs and DTORs are very important for MS DLLs
  public:
    DefaultEncryptor() { }  
    virtual ~DefaultEncryptor() { }

  };
} // NAMESPACE