/**
* OWASP Enterprise Security API (ESAPI)
*
* This file is part of the Open Web Application Security Project (OWASP)
* Enterprise Security API (ESAPI) project. For details, please see
* http://www.owasp.org/index.php/ESAPI.
*
* Copyright (c) 2011 - The OWASP Foundation
*
* @author Kevin Wall, kevin.w.wall@gmail.com
* @author Jeffrey Walton, noloader@gmail.com
*
*/

#include "crypto/RandomPool.h"
#include "util/ArrayZeroizer.h"
#include "errors/EncryptionException.h"
#include "errors/InvalidArgumentException.h"

namespace esapi
{
  /**
  * A lock for the internal operations. Its static because GetSharedIntstance()
  * serves up a single static object. Before the first construction of the static
  * object, the lock is acquired.
  */
  Mutex& RandomPool::GetSharedLock()
  {
    static Mutex s_lock;
    return s_lock;
  }

  /**
  * Create a random pool. Users must call GetSharedInstance().
  */
  RandomPool::RandomPool( ) : m_keyed(false)
  {
  }

  /**
  * Initialize the random pool.
  */
  void RandomPool::Init()
  {
    Reseed();
  }

  /**
  * Destroy the random pool.
  */
  RandomPool::~RandomPool( )
  {
  }

  /**
  * Reseeds the random pool by setting a key and IV from OS acquired entropy.
  */
  void RandomPool::Reseed()
  {
    // Forward facing function. Lock the object to ensure state integrity.
    MutexLock lock(RandomPool::GetSharedLock());

    try
    {
      m_keyed = false;

      // Key and IV
      byte key[32 /*AES256 key*/ + 16 /*AES Blocksize*/];
      ByteArrayZeroizer(key, sizeof(key));

      if(GenerateKey(key, sizeof(key)))
      {      
        CryptoPP::SHA512 hash;

        // Hash key in place
        hash.Update(key, 32);
        hash.TruncatedFinal(key, 32);

        // Hash iv in place
        hash.Update(key+32, 16);
        hash.TruncatedFinal(key+32, 16);

        m_cipher.SetKeyWithIV(key, 32, key+32);
        m_keyed = true;
      }
    }
    catch(CryptoPP::Exception& ex)
    {
      throw EncryptionException(std::string("Internal error: ") + ex.what());
    }
  }

  RandomPool& RandomPool::GetSharedInstance()
  {
    static volatile bool init = false;
    static RandomPool s_pool;

    if(!init)
    {
      // Forward facing function. Lock the object to ensure state integrity.
      MutexLock lock(RandomPool::GetSharedLock());

      if(!init)
      {
        s_pool.Init();
        init = true;
      }
    }

    return s_pool;
  }

  /**
  * Retrieve bytes form the random pool.
  */
  void RandomPool::GenerateBlock(byte* bytes, size_t size)
  {
    // Forward facing function. Lock the object to ensure state integrity.
    MutexLock lock(RandomPool::GetSharedLock());

    ASSERT(bytes && size);
    if( !(bytes && size) )
      throw InvalidArgumentException("The buffer or size is not valid");

    if(!m_keyed)
      throw EncryptionException("Failed to generate a block in the random pool (1)");

    try
    {
      byte data[CryptoPP::AES::BLOCKSIZE];
      ByteArrayZeroizer z1(data, sizeof(data));

      if(!GetTimeData(data, sizeof(data)))
        throw EncryptionException("Failed to generate a block in the random pool (2)");

      size_t idx = 0;
      while(size)
      {
        // Always process a full block.
        m_cipher.ProcessData(data, data, sizeof(data));

        const size_t req = std::min(size, (size_t)CryptoPP::AES::BLOCKSIZE);
        ::memcpy(bytes+idx, data, req);

        idx += req;
        size -= req;
      }
    }
    catch(CryptoPP::Exception& ex)
    {
      throw EncryptionException(std::string("Internal error: ") + ex.what());
    }
  }
}
