/*-----------------------------------------------------------------------------------------------------------
  This software is licensed under the Microsoft Public License (Ms-PL).
  For more information about Microsoft open source licenses, refer to
  http://www.microsoft.com/opensource/licenses.mspx

  This license governs use of the accompanying software. If you use the software, you accept this license.
  If you do not accept the license, do not use the software.

  Definitions
  The terms "reproduce," "reproduction," "derivative works," and "distribution" have the same meaning here
  as under U.S. copyright law. A "contribution" is the original software, or any additions or changes to
  the software. A "contributor" is any person that distributes its contribution under this license.
  "Licensed patents" are a contributor's patent claims that read directly on its contribution.

  Grant of Rights
  (A) Copyright Grant- Subject to the terms of this license, including the license conditions and limitations
  in section 3, each contributor grants you a non-exclusive, worldwide, royalty-free copyright license to
  reproduce its contribution, prepare derivative works of its contribution, and distribute its contribution
  or any derivative works that you create.

  (B) Patent Grant- Subject to the terms of this license, including the license conditions and limitations in
  section 3, each contributor grants you a non-exclusive, worldwide, royalty-free license under its licensed
  patents to make, have made, use, sell, offer for sale, import, and/or otherwise dispose of its contribution
  in the software or derivative works of the contribution in the software.

  Conditions and Limitations
  (A) No Trademark License- This license does not grant you rights to use any contributors' name, logo,
  or trademarks.
  (B) If you bring a patent claim against any contributor over patents that you claim are infringed by the
  software, your patent license from such contributor to the software ends automatically.
  (C) If you distribute any portion of the software, you must retain all copyright, patent, trademark, and
  attribution notices that are present in the software.
  (D) If you distribute any portion of the software in source code form, you may do so only under this license
  by including a complete copy of this license with your distribution. If you distribute any portion of the
  software in compiled or object code form, you may only do so under a license that complies with this license.
  (E) The software is licensed "as-is." You bear the risk of using it. The contributors give no express warranties,
  guarantees, or conditions. You may have additional consumer rights under your local laws which this license
  cannot change. To the extent permitted under your local laws, the contributors exclude the implied warranties
  of merchantability, fitness for a particular purpose and non-infringement.

  Copyright (c) OWASP Project (https://www.owasp.org), 2011. All rights reserved.
*/

#include "TestMain.h"

/*
 * Interesting numbers:
 *
 *  unsigned __int64
 *  0, 1, 2, 0x7fffffff, 0x80000000, 0xffffffff, 0x100000000, 0x200000000, 0x7fffffffffffffff, 0x8000000000000000, 0xffffffffffffffff
 *  unsigned __int32
 *  0, 1, 2, 0x7fffffff, 0x80000000, 0xffffffff
 *  signed __int64
 *  0, 1, 2, 0x7fffffff, 0x80000000, 0xffffffff, 0x100000000, 0x200000000, 0x7fffffffffffffff, 0x8000000000000000, 0xffffffffffffffff
 */

namespace mult_verify
{

  template <typename T, typename U>
  struct MultTest
  {
    T x;
    U y;
    bool fExpected;
  };

  static const MultTest< unsigned __int64, unsigned __int64 > uint64_uint64[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffffULL,            0ULL, true },
      { 0x80000000ULL,            0ULL, true },
      { 0xffffffffULL,            0ULL, true },
      { 0x100000000ULL,           0ULL, true },
      { 0x200000000ULL,           0ULL, true },
      { 0x7fffffffffffffffULL,    0ULL, true },
      { 0x8000000000000000ULL,    0ULL, true },
      { 0xffffffffffffffffULL,    0ULL, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffffULL,            1ULL, true },
      { 0x80000000ULL,            1ULL, true },
      { 0xffffffffULL,            1ULL, true },
      { 0x100000000ULL,           1ULL, true },
      { 0x200000000ULL,           1ULL, true },
      { 0x7fffffffffffffffULL,    1ULL, true },
      { 0x8000000000000000ULL,    1ULL, true },
      { 0xffffffffffffffffULL,    1ULL, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffffULL,            2ULL, true },
      { 0x80000000ULL,            2ULL, true },
      { 0xffffffffULL,            2ULL, true },
      { 0x100000000ULL,           2ULL, true },
      { 0x200000000ULL,           2ULL, true },
      { 0x7fffffffffffffffULL,    2ULL, true },
      { 0x8000000000000000ULL,    2ULL, false },
      { 0xffffffffffffffffULL,    2ULL, false },
      { 0ULL,                     0x7fffffffULL, true },
      { 1ULL,                     0x7fffffffULL, true },
      { 2ULL,                     0x7fffffffULL, true },
      { 0x7fffffffULL,            0x7fffffffULL, true },
      { 0x80000000ULL,            0x7fffffffULL, true },
      { 0xffffffffULL,            0x7fffffffULL, true },
      { 0x100000000ULL,           0x7fffffffULL, true },
      { 0x200000000ULL,           0x7fffffffULL, true },
      { 0x7fffffffffffffffULL,    0x7fffffffULL, false },
      { 0x8000000000000000ULL,    0x7fffffffULL, false },
      { 0xffffffffffffffffULL,    0x7fffffffULL, false },
      { 0ULL,                     0x80000000ULL, true },
      { 1ULL,                     0x80000000ULL, true },
      { 2ULL,                     0x80000000ULL, true },
      { 0x7fffffffULL,            0x80000000ULL, true },
      { 0x80000000ULL,            0x80000000ULL, true },
      { 0xffffffffULL,            0x80000000ULL, true },
      { 0x100000000ULL,           0x80000000ULL, true },
      { 0x200000000ULL,           0x80000000ULL, false },
      { 0x7fffffffffffffffULL,    0x80000000ULL, false },
      { 0x8000000000000000ULL,    0x80000000ULL, false },
      { 0xffffffffffffffffULL,    0x80000000ULL, false },
      { 0ULL,                     0xffffffffULL, true },
      { 1ULL,                     0xffffffffULL, true },
      { 2ULL,                     0xffffffffULL, true },
      { 0x7fffffffULL,            0xffffffffULL, true },
      { 0x80000000ULL,            0xffffffffULL, true },
      { 0xffffffffULL,            0xffffffffULL, true },
      { 0x100000000ULL,           0xffffffffULL, true },
      { 0x200000000ULL,           0xffffffffULL, false },
      { 0x7fffffffffffffffULL,    0xffffffffULL, false },
      { 0x8000000000000000ULL,    0xffffffffULL, false },
      { 0xffffffffffffffffULL,    0xffffffffULL, false },
      { 0ULL,                     0x100000000ULL, true },
      { 1ULL,                     0x100000000ULL, true },
      { 2ULL,                     0x100000000ULL, true },
      { 0x7fffffffULL,            0x100000000ULL, true },
      { 0x80000000ULL,            0x100000000ULL, true },
      { 0xffffffffULL,            0x100000000ULL, true },
      { 0x100000000ULL,           0x100000000ULL, false },
      { 0x200000000ULL,           0x100000000ULL, false },
      { 0x7fffffffffffffffULL,    0x100000000ULL, false },
      { 0x8000000000000000ULL,    0x100000000ULL, false },
      { 0xffffffffffffffffULL,    0x100000000ULL, false },
      { 0ULL,                     0x200000000ULL, true },
      { 1ULL,                     0x200000000ULL, true },
      { 2ULL,                     0x200000000ULL, true },
      { 0x7fffffffULL,            0x200000000ULL, true },
      { 0x80000000ULL,            0x200000000ULL, false },
      { 0xffffffffULL,            0x200000000ULL, false },
      { 0x100000000ULL,           0x200000000ULL, false },
      { 0x200000000ULL,           0x200000000ULL, false },
      { 0x7fffffffffffffffULL,    0x200000000ULL, false },
      { 0x8000000000000000ULL,    0x200000000ULL, false },
      { 0xffffffffffffffffULL,    0x200000000ULL, false },
      { 0ULL,                     0x7fffffffffffffffULL, true },
      { 1ULL,                     0x7fffffffffffffffULL, true },
      { 2ULL,                     0x7fffffffffffffffULL, true },
      { 0x7fffffffULL,            0x7fffffffffffffffULL, false },
      { 0x80000000ULL,            0x7fffffffffffffffULL, false },
      { 0xffffffffULL,            0x7fffffffffffffffULL, false },
      { 0x100000000ULL,           0x7fffffffffffffffULL, false },
      { 0x200000000ULL,           0x7fffffffffffffffULL, false },
      { 0x7fffffffffffffffULL,    0x7fffffffffffffffULL, false },
      { 0x8000000000000000ULL,    0x7fffffffffffffffULL, false },
      { 0xffffffffffffffffULL,    0x7fffffffffffffffULL, false },
      { 0ULL,                     0x8000000000000000ULL, true },
      { 1ULL,                     0x8000000000000000ULL, true },
      { 2ULL,                     0x8000000000000000ULL, false },
      { 0x7fffffffULL,            0x8000000000000000ULL, false },
      { 0x80000000ULL,            0x8000000000000000ULL, false },
      { 0xffffffffULL,            0x8000000000000000ULL, false },
      { 0x100000000ULL,           0x8000000000000000ULL, false },
      { 0x200000000ULL,           0x8000000000000000ULL, false },
      { 0x7fffffffffffffffULL,    0x8000000000000000ULL, false },
      { 0x8000000000000000ULL,    0x8000000000000000ULL, false },
      { 0xffffffffffffffffULL,    0x8000000000000000ULL, false },
      { 0ULL,                     0xffffffffffffffffULL, true },
      { 1ULL,                     0xffffffffffffffffULL, true },
      { 2ULL,                     0xffffffffffffffffULL, false },
      { 0x7fffffffULL,            0xffffffffffffffffULL, false },
      { 0x80000000ULL,            0xffffffffffffffffULL, false },
      { 0xffffffffULL,            0xffffffffffffffffULL, false },
      { 0x100000000ULL,           0xffffffffffffffffULL, false },
      { 0x200000000ULL,           0xffffffffffffffffULL, false },
      { 0x7fffffffffffffffULL,    0xffffffffffffffffULL, false },
      { 0x8000000000000000ULL,    0xffffffffffffffffULL, false },
      { 0xffffffffffffffffULL,    0xffffffffffffffffULL, false },
      // Special case - force addition overflow case
      { 0xffffffffULL,            0x100000002ULL, false }
    };

  void MultVerifyUint64Uint64()
  {
    size_t i;

    for( i = 0; i < COUNTOF(uint64_uint64); ++i )
      {
        unsigned __int64 ret;
        if( SafeMultiply(uint64_uint64[i].x, uint64_uint64[i].y, ret) != uint64_uint64[i].fExpected )
          {
            //assert(false);
            // printf("Error in case uint64_uint64: %I64X, %I64X, expected = %s\n",
            // uint64_uint64[i].x, uint64_uint64[i].y, uint64_uint64[i].fExpected ? "true" : "false");
            cerr << "Error in case uint64_uint64: ";
            cerr << hex << setw(16) << setfill('0') << uint64_uint64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint64_uint64[i].y << ", ";
            cerr << "expected = " << uint64_uint64[i].fExpected << endl;
          }

        // Now test throwing version
        bool fSuccess = true;
        try
          {
            SafeInt<unsigned __int64> si(uint64_uint64[i].x);
            si *= uint64_uint64[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != uint64_uint64[i].fExpected )
          {
            // printf("Error in case uint64_uint64 throw: %I64X, %I64X, expected = %s\n",
            // uint64_uint64[i].x, uint64_uint64[i].y, uint64_uint64[i].fExpected ? "true" : "false");
            cerr << "Error in case uint64_uint64 throw: ";
            cerr << hex << setw(16) << setfill('0') << uint64_uint64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint64_uint64[i].y << ", ";
            cerr << "expected = " << uint64_uint64[i].fExpected << endl;
          }
      }
  }

  static const MultTest< unsigned __int64, unsigned __int32 > uint64_uint32[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffffULL,            0, true },
      { 0x80000000ULL,            0, true },
      { 0xffffffffULL,            0, true },
      { 0x100000000ULL,           0, true },
      { 0x200000000ULL,           0, true },
      { 0x7fffffffffffffffULL,    0, true },
      { 0x8000000000000000ULL,    0, true },
      { 0xffffffffffffffffULL,    0, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffffULL,            1, true },
      { 0x80000000ULL,            1, true },
      { 0xffffffffULL,            1, true },
      { 0x100000000ULL,           1, true },
      { 0x200000000ULL,           1, true },
      { 0x7fffffffffffffffULL,    1, true },
      { 0x8000000000000000ULL,    1, true },
      { 0xffffffffffffffffULL,    1, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffffULL,            2, true },
      { 0x80000000ULL,            2, true },
      { 0xffffffffULL,            2, true },
      { 0x100000000ULL,           2, true },
      { 0x200000000ULL,           2, true },
      { 0x7fffffffffffffffULL,    2, true },
      { 0x8000000000000000ULL,    2, false },
      { 0xffffffffffffffffULL,    2, false },
      { 0ULL,                     0x7fffffff, true },
      { 1ULL,                     0x7fffffff, true },
      { 2ULL,                     0x7fffffff, true },
      { 0x7fffffffULL,            0x7fffffff, true },
      { 0x80000000ULL,            0x7fffffff, true },
      { 0xffffffffULL,            0x7fffffff, true },
      { 0x100000000ULL,           0x7fffffff, true },
      { 0x200000000ULL,           0x7fffffff, true },
      { 0x7fffffffffffffffULL,    0x7fffffff, false },
      { 0x8000000000000000ULL,    0x7fffffff, false },
      { 0xffffffffffffffffULL,    0x7fffffff, false },
      { 0ULL,                     0x80000000, true },
      { 1ULL,                     0x80000000, true },
      { 2ULL,                     0x80000000, true },
      { 0x7fffffffULL,            0x80000000, true },
      { 0x80000000ULL,            0x80000000, true },
      { 0xffffffffULL,            0x80000000, true },
      { 0x100000000ULL,           0x80000000, true },
      { 0x200000000ULL,           0x80000000, false },
      { 0x7fffffffffffffffULL,    0x80000000, false },
      { 0x8000000000000000ULL,    0x80000000, false },
      { 0xffffffffffffffffULL,    0x80000000, false },
      { 0ULL,                     0xffffffff, true },
      { 1ULL,                     0xffffffff, true },
      { 2ULL,                     0xffffffff, true },
      { 0x7fffffffULL,            0xffffffff, true },
      { 0x80000000ULL,            0xffffffff, true },
      { 0xffffffffULL,            0xffffffff, true },
      { 0x100000000ULL,           0xffffffff, true },
      { 0x200000000ULL,           0xffffffff, false },
      { 0x7fffffffffffffffULL,    0xffffffff, false },
      { 0x8000000000000000ULL,    0xffffffff, false },
      { 0xffffffffffffffffULL,    0xffffffff, false }
    };

  void MultVerifyUint64Uint()
  {
    size_t i;

    for( i = 0; i < COUNTOF(uint64_uint32); ++i )
      {
        unsigned __int64 ret;
        if( SafeMultiply(uint64_uint32[i].x, uint64_uint32[i].y, ret) != uint64_uint32[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // uint64_uint32[i].x, uint64_uint32[i].y, uint64_uint32[i].fExpected ? "true" : "false");
            cerr << "Error in case uint64_uint32: ";
            cerr << hex << setw(16) << setfill('0') << uint64_uint32[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint64_uint32[i].y << ", ";
            cerr << "expected = " << uint64_uint32[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<unsigned __int64> si(uint64_uint32[i].x);
            si *= uint64_uint32[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != uint64_uint32[i].fExpected )
          {
            // printf("Error in case uint64_uint32 throw: %I64X, %I64X, expected = %s\n",
            // uint64_uint32[i].x, uint64_uint32[i].y, uint64_uint32[i].fExpected ? "true" : "false");
            cerr << "Error in case uint64_uint32 throw: ";
            cerr << hex << setw(16) << setfill('0') << uint64_uint32[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint64_uint32[i].y << ", ";
            cerr << "expected = " << uint64_uint32[i].fExpected << endl;
          }
      }
  }

  static const MultTest< unsigned __int32, unsigned __int64 > uint32_uint64[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffff,            0ULL, true },
      { 0x80000000,            0ULL, true },
      { 0xffffffff,            0ULL, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffff,            1ULL, true },
      { 0x80000000,            1ULL, true },
      { 0xffffffff,            1ULL, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffff,            2ULL, true },
      { 0x80000000,            2ULL, false },
      { 0xffffffff,            2ULL, false },
      { 0,                     0x7fffffffULL, true },
      { 1,                     0x7fffffffULL, true },
      { 2,                     0x7fffffffULL, true },
      { 0x7fffffff,            0x7fffffffULL, false },
      { 0x80000000,            0x7fffffffULL, false },
      { 0xffffffff,            0x7fffffffULL, false },
      { 0,                     0x80000000ULL, true },
      { 1,                     0x80000000ULL, true },
      { 2,                     0x80000000ULL, false },
      { 0x7fffffff,            0x80000000ULL, false },
      { 0x80000000,            0x80000000ULL, false },
      { 0xffffffff,            0x80000000ULL, false },
      { 0,                     0xffffffffULL, true },
      { 1,                     0xffffffffULL, true },
      { 2,                     0xffffffffULL, false },
      { 0x7fffffff,            0xffffffffULL, false },
      { 0x80000000,            0xffffffffULL, false },
      { 0xffffffff,            0xffffffffULL, false },
      { 0,                     0x100000000ULL, true },
      { 1,                     0x100000000ULL, false },
      { 2,                     0x100000000ULL, false },
      { 0x7fffffff,            0x100000000ULL, false },
      { 0x80000000,            0x100000000ULL, false },
      { 0xffffffff,            0x100000000ULL, false },
      { 0,                     0x200000000ULL, true },
      { 1,                     0x200000000ULL, false },
      { 2,                     0x200000000ULL, false },
      { 0x7fffffff,            0x200000000ULL, false },
      { 0x80000000,            0x200000000ULL, false },
      { 0xffffffff,            0x200000000ULL, false },
      { 0,                     0x7fffffffffffffffULL, true },
      { 1,                     0x7fffffffffffffffULL, false },
      { 2,                     0x7fffffffffffffffULL, false },
      { 0x7fffffff,            0x7fffffffffffffffULL, false },
      { 0x80000000,            0x7fffffffffffffffULL, false },
      { 0xffffffff,            0x7fffffffffffffffULL, false },
      { 0,                     0x8000000000000000ULL, true },
      { 1,                     0x8000000000000000ULL, false },
      { 2,                     0x8000000000000000ULL, false },
      { 0x7fffffff,            0x8000000000000000ULL, false },
      { 0x80000000,            0x8000000000000000ULL, false },
      { 0xffffffff,            0x8000000000000000ULL, false },
      { 0,                     0xffffffffffffffffULL, true },
      { 1,                     0xffffffffffffffffULL, false },
      { 2,                     0xffffffffffffffffULL, false },
      { 0x7fffffff,            0xffffffffffffffffULL, false },
      { 0x80000000,            0xffffffffffffffffULL, false },
      { 0xffffffff,            0xffffffffffffffffULL, false }
    };

  void MultVerifyUintUint64()
  {
    size_t i;

    for( i = 0; i < COUNTOF(uint32_uint64); ++i )
      {
        unsigned __int32 ret;
        if( SafeMultiply(uint32_uint64[i].x, uint32_uint64[i].y, ret) != uint32_uint64[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // uint32_uint64[i].x, uint32_uint64[i].y, uint32_uint64[i].fExpected ? "true" : "false");
            cerr << "Error in case uint32_uint64: ";
            cerr << hex << setw(16) << setfill('0') << uint32_uint64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint32_uint64[i].y << ", ";
            cerr << "expected = " << uint32_uint64[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<unsigned __int32> si(uint32_uint64[i].x);
            si *= uint32_uint64[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != uint32_uint64[i].fExpected )
          {
            // printf("Error in case uint32_uint64 throw: %I64X, %I64X, expected = %s\n",
            // uint32_uint64[i].x, uint32_uint64[i].y, uint32_uint64[i].fExpected ? "true" : "false");
            cerr << "Error in case uint32_uint64 throw: ";
            cerr << hex << setw(16) << setfill('0') << uint32_uint64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint32_uint64[i].y << ", ";
            cerr << "expected = " << uint32_uint64[i].fExpected << endl;
          }
      }
  }

  static const MultTest< unsigned __int32, __int64 > uint32_int64[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffff,            0LL, true },
      { 0x80000000,            0LL, true },
      { 0xffffffff,            0LL, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffff,            1LL, true },
      { 0x80000000,            1LL, true },
      { 0xffffffff,            1LL, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffff,            2LL, true },
      { 0x80000000,            2LL, false },
      { 0xffffffff,            2LL, false },
      { 0,                     0x7fffffffLL, true },
      { 1,                     0x7fffffffLL, true },
      { 2,                     0x7fffffffLL, true },
      { 0x7fffffff,            0x7fffffffLL, false },
      { 0x80000000,            0x7fffffffLL, false },
      { 0xffffffff,            0x7fffffffLL, false },
      { 0,                     0x80000000LL, true },
      { 1,                     0x80000000LL, true },
      { 2,                     0x80000000LL, false },
      { 0x7fffffff,            0x80000000LL, false },
      { 0x80000000,            0x80000000LL, false },
      { 0xffffffff,            0x80000000LL, false },
      { 0,                     0xffffffffLL, true },
      { 1,                     0xffffffffLL, true },
      { 2,                     0xffffffffLL, false },
      { 0x7fffffff,            0xffffffffLL, false },
      { 0x80000000,            0xffffffffLL, false },
      { 0xffffffff,            0xffffffffLL, false },
      { 0,                     0x100000000LL, true },
      { 1,                     0x100000000LL, false },
      { 2,                     0x100000000LL, false },
      { 0x7fffffff,            0x100000000LL, false },
      { 0x80000000,            0x100000000LL, false },
      { 0xffffffff,            0x100000000LL, false },
      { 0,                     0x200000000LL, true },
      { 1,                     0x200000000LL, false },
      { 2,                     0x200000000LL, false },
      { 0x7fffffff,            0x200000000LL, false },
      { 0x80000000,            0x200000000LL, false },
      { 0xffffffff,            0x200000000LL, false },
      { 0,                     0x7fffffffffffffffLL, true },
      { 1,                     0x7fffffffffffffffLL, false },
      { 2,                     0x7fffffffffffffffLL, false },
      { 0x7fffffff,            0x7fffffffffffffffLL, false },
      { 0x80000000,            0x7fffffffffffffffLL, false },
      { 0xffffffff,            0x7fffffffffffffffLL, false },
      { 0,                     0x8000000000000000LL, true },
      { 1,                     0x8000000000000000LL, false },
      { 2,                     0x8000000000000000LL, false },
      { 0x7fffffff,            0x8000000000000000LL, false },
      { 0x80000000,            0x8000000000000000LL, false },
      { 0xffffffff,            0x8000000000000000LL, false },
      { 0,                     0xffffffffffffffffLL, true },
      { 1,                     0xffffffffffffffffLL, false },
      { 2,                     0xffffffffffffffffLL, false },
      { 0x7fffffff,            0xffffffffffffffffLL, false },
      { 0x80000000,            0xffffffffffffffffLL, false },
      { 0xffffffff,            0xffffffffffffffffLL, false }
    };

  void MultVerifyUintInt64()
  {
    size_t i;

    for( i = 0; i < COUNTOF(uint32_int64); ++i )
      {
        unsigned __int32 ret;
        if( SafeMultiply(uint32_int64[i].x, uint32_int64[i].y, ret) != uint32_int64[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // uint32_int64[i].x, uint32_int64[i].y, uint32_int64[i].fExpected ? "true" : "false");
            cerr << "Error in case uint32_int64: ";
            cerr << hex << setw(16) << setfill('0') << uint32_int64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint32_int64[i].y << ", ";
            cerr << "expected = " << uint32_int64[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<unsigned __int32> si(uint32_int64[i].x);
            si *= uint32_int64[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != uint32_int64[i].fExpected )
          {
            // printf("Error in case uint32_int64 throw: %I64X, %I64X, expected = %s\n",
            // uint32_int64[i].x, uint32_int64[i].y, uint32_int64[i].fExpected ? "true" : "false");
            cerr << "Error in case uint32_int64 throw: ";
            cerr << hex << setw(16) << setfill('0') << uint32_int64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint32_int64[i].y << ", ";
            cerr << "expected = " << uint32_int64[i].fExpected << endl;
          }
      }
  }

  static const MultTest< unsigned __int64, __int64 > uint64_int64[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffffULL,            0LL, true },
      { 0x80000000ULL,            0LL, true },
      { 0xffffffffULL,            0LL, true },
      { 0x100000000ULL,           0LL, true },
      { 0x200000000ULL,           0LL, true },
      { 0x7fffffffffffffffULL,    0LL, true },
      { 0x8000000000000000ULL,    0LL, true },
      { 0xffffffffffffffffULL,    0LL, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffffULL,            1LL, true },
      { 0x80000000ULL,            1LL, true },
      { 0xffffffffULL,            1LL, true },
      { 0x100000000ULL,           1LL, true },
      { 0x200000000ULL,           1LL, true },
      { 0x7fffffffffffffffULL,    1LL, true },
      { 0x8000000000000000ULL,    1LL, true },
      { 0xffffffffffffffffULL,    1LL, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffffULL,            2LL, true },
      { 0x80000000ULL,            2LL, true },
      { 0xffffffffULL,            2LL, true },
      { 0x100000000ULL,           2LL, true },
      { 0x200000000ULL,           2LL, true },
      { 0x7fffffffffffffffULL,    2LL, true },
      { 0x8000000000000000ULL,    2LL, false },
      { 0xffffffffffffffffULL,    2LL, false },
      { 0ULL,                     0x7fffffffLL, true },
      { 1ULL,                     0x7fffffffLL, true },
      { 2ULL,                     0x7fffffffLL, true },
      { 0x7fffffffULL,            0x7fffffffLL, true },
      { 0x80000000ULL,            0x7fffffffLL, true },
      { 0xffffffffULL,            0x7fffffffLL, true },
      { 0x100000000ULL,           0x7fffffffLL, true },
      { 0x200000000ULL,           0x7fffffffLL, true },
      { 0x7fffffffffffffffULL,    0x7fffffffLL, false },
      { 0x8000000000000000ULL,    0x7fffffffLL, false },
      { 0xffffffffffffffffULL,    0x7fffffffLL, false },
      { 0ULL,                     0x80000000LL, true },
      { 1ULL,                     0x80000000LL, true },
      { 2ULL,                     0x80000000LL, true },
      { 0x7fffffffULL,            0x80000000LL, true },
      { 0x80000000ULL,            0x80000000LL, true },
      { 0xffffffffULL,            0x80000000LL, true },
      { 0x100000000ULL,           0x80000000LL, true },
      { 0x200000000ULL,           0x80000000LL, false },
      { 0x7fffffffffffffffULL,    0x80000000LL, false },
      { 0x8000000000000000ULL,    0x80000000LL, false },
      { 0xffffffffffffffffULL,    0x80000000LL, false },
      { 0ULL,                     0xffffffffLL, true },
      { 1ULL,                     0xffffffffLL, true },
      { 2ULL,                     0xffffffffLL, true },
      { 0x7fffffffULL,            0xffffffffLL, true },
      { 0x80000000ULL,            0xffffffffLL, true },
      { 0xffffffffULL,            0xffffffffLL, true },
      { 0x100000000ULL,           0xffffffffLL, true },
      { 0x200000000ULL,           0xffffffffLL, false },
      { 0x7fffffffffffffffULL,    0xffffffffLL, false },
      { 0x8000000000000000ULL,    0xffffffffLL, false },
      { 0xffffffffffffffffULL,    0xffffffffLL, false },
      { 0ULL,                     0x100000000LL, true },
      { 1ULL,                     0x100000000LL, true },
      { 2ULL,                     0x100000000LL, true },
      { 0x7fffffffULL,            0x100000000LL, true },
      { 0x80000000ULL,            0x100000000LL, true },
      { 0xffffffffULL,            0x100000000LL, true },
      { 0x100000000ULL,           0x100000000LL, false },
      { 0x200000000ULL,           0x100000000LL, false },
      { 0x7fffffffffffffffULL,    0x100000000LL, false },
      { 0x8000000000000000ULL,    0x100000000LL, false },
      { 0xffffffffffffffffULL,    0x100000000LL, false },
      { 0ULL,                     0x200000000LL, true },
      { 1ULL,                     0x200000000LL, true },
      { 2ULL,                     0x200000000LL, true },
      { 0x7fffffffULL,            0x200000000LL, true },
      { 0x80000000ULL,            0x200000000LL, false },
      { 0xffffffffULL,            0x200000000LL, false },
      { 0x100000000ULL,           0x200000000LL, false },
      { 0x200000000ULL,           0x200000000LL, false },
      { 0x7fffffffffffffffULL,    0x200000000LL, false },
      { 0x8000000000000000ULL,    0x200000000LL, false },
      { 0xffffffffffffffffULL,    0x200000000LL, false },
      { 0ULL,                     0x7fffffffffffffffLL, true },
      { 1ULL,                     0x7fffffffffffffffLL, true },
      { 2ULL,                     0x7fffffffffffffffLL, true },
      { 0x7fffffffULL,            0x7fffffffffffffffLL, false },
      { 0x80000000ULL,            0x7fffffffffffffffLL, false },
      { 0xffffffffULL,            0x7fffffffffffffffLL, false },
      { 0x100000000ULL,           0x7fffffffffffffffLL, false },
      { 0x200000000ULL,           0x7fffffffffffffffLL, false },
      { 0x7fffffffffffffffULL,    0x7fffffffffffffffLL, false },
      { 0x8000000000000000ULL,    0x7fffffffffffffffLL, false },
      { 0xffffffffffffffffULL,    0x7fffffffffffffffLL, false },
      { 0ULL,                     0x8000000000000000LL, true },
      { 1ULL,                     0x8000000000000000LL, false },
      { 2ULL,                     0x8000000000000000LL, false },
      { 0x7fffffffULL,            0x8000000000000000LL, false },
      { 0x80000000ULL,            0x8000000000000000LL, false },
      { 0xffffffffULL,            0x8000000000000000LL, false },
      { 0x100000000ULL,           0x8000000000000000LL, false },
      { 0x200000000ULL,           0x8000000000000000LL, false },
      { 0x7fffffffffffffffULL,    0x8000000000000000LL, false },
      { 0x8000000000000000ULL,    0x8000000000000000LL, false },
      { 0xffffffffffffffffULL,    0x8000000000000000LL, false },
      { 0ULL,                     0xffffffffffffffffLL, true },
      { 1ULL,                     0xffffffffffffffffLL, false },
      { 2ULL,                     0xffffffffffffffffLL, false },
      { 0x7fffffffULL,            0xffffffffffffffffLL, false },
      { 0x80000000ULL,            0xffffffffffffffffLL, false },
      { 0xffffffffULL,            0xffffffffffffffffLL, false },
      { 0x100000000ULL,           0xffffffffffffffffLL, false },
      { 0x200000000ULL,           0xffffffffffffffffLL, false },
      { 0x7fffffffffffffffULL,    0xffffffffffffffffLL, false },
      { 0x8000000000000000ULL,    0xffffffffffffffffLL, false },
      { 0xffffffffffffffffULL,    0xffffffffffffffffLL, false }
    };

  void MultVerifyUint64Int64()
  {
    size_t i;

    for( i = 0; i < COUNTOF(uint64_int64); ++i )
      {
        unsigned __int64 ret;
        if( SafeMultiply(uint64_int64[i].x, uint64_int64[i].y, ret) != uint64_int64[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // uint64_int64[i].x, uint64_int64[i].y, uint64_int64[i].fExpected ? "true" : "false");
            cerr << "Error in case uint64_int64: ";
            cerr << hex << setw(16) << setfill('0') << uint64_int64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint64_int64[i].y << ", ";
            cerr << "expected = " << uint64_int64[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<unsigned __int64> si(uint64_int64[i].x);
            si *= uint64_int64[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != uint64_int64[i].fExpected )
          {
            // printf("Error in case uint64_int64 throw: %I64X, %I64X, expected = %s\n",
            // uint64_int64[i].x, uint64_int64[i].y, uint64_int64[i].fExpected ? "true" : "false");
            cerr << "Error in case uint64_int64 throw: ";
            cerr << hex << setw(16) << setfill('0') << uint64_int64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint64_int64[i].y << ", ";
            cerr << "expected = " << uint64_int64[i].fExpected << endl;
          }
      }
  }

  static const MultTest< unsigned __int64, __int32 > uint64_int32[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffffULL,            0, true },
      { 0x80000000ULL,            0, true },
      { 0xffffffffULL,            0, true },
      { 0x100000000ULL,           0, true },
      { 0x200000000ULL,           0, true },
      { 0x7fffffffffffffffULL,    0, true },
      { 0x8000000000000000ULL,    0, true },
      { 0xffffffffffffffffULL,    0, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffffULL,            1, true },
      { 0x80000000ULL,            1, true },
      { 0xffffffffULL,            1, true },
      { 0x100000000ULL,           1, true },
      { 0x200000000ULL,           1, true },
      { 0x7fffffffffffffffULL,    1, true },
      { 0x8000000000000000ULL,    1, true },
      { 0xffffffffffffffffULL,    1, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffffULL,            2, true },
      { 0x80000000ULL,            2, true },
      { 0xffffffffULL,            2, true },
      { 0x100000000ULL,           2, true },
      { 0x200000000ULL,           2, true },
      { 0x7fffffffffffffffULL,    2, true },
      { 0x8000000000000000ULL,    2, false },
      { 0xffffffffffffffffULL,    2, false },
      { 0ULL,                     0x7fffffff, true },
      { 1ULL,                     0x7fffffff, true },
      { 2ULL,                     0x7fffffff, true },
      { 0x7fffffffULL,            0x7fffffff, true },
      { 0x80000000ULL,            0x7fffffff, true },
      { 0xffffffffULL,            0x7fffffff, true },
      { 0x100000000ULL,           0x7fffffff, true },
      { 0x200000000ULL,           0x7fffffff, true },
      { 0x7fffffffffffffffULL,    0x7fffffff, false },
      { 0x8000000000000000ULL,    0x7fffffff, false },
      { 0xffffffffffffffffULL,    0x7fffffff, false },
      { 0ULL,                     0x80000000, true },
      { 1ULL,                     0x80000000, false },
      { 2ULL,                     0x80000000, false },
      { 0x7fffffffULL,            0x80000000, false },
      { 0x80000000ULL,            0x80000000, false },
      { 0xffffffffULL,            0x80000000, false },
      { 0x100000000ULL,           0x80000000, false },
      { 0x200000000ULL,           0x80000000, false },
      { 0x7fffffffffffffffULL,    0x80000000, false },
      { 0x8000000000000000ULL,    0x80000000, false },
      { 0xffffffffffffffffULL,    0x80000000, false },
      { 0ULL,                     0xffffffff, true },
      { 1ULL,                     0xffffffff, false },
      { 2ULL,                     0xffffffff, false },
      { 0x7fffffffULL,            0xffffffff, false },
      { 0x80000000ULL,            0xffffffff, false },
      { 0xffffffffULL,            0xffffffff, false },
      { 0x100000000ULL,           0xffffffff, false },
      { 0x200000000ULL,           0xffffffff, false },
      { 0x7fffffffffffffffULL,    0xffffffff, false },
      { 0x8000000000000000ULL,    0xffffffff, false },
      { 0xffffffffffffffffULL,    0xffffffff, false }
    };

  void MultVerifyUint64Int()
  {
    size_t i;

    for( i = 0; i < COUNTOF(uint64_int32); ++i )
      {
        unsigned __int64 ret;
        if( SafeMultiply(uint64_int32[i].x, uint64_int32[i].y, ret) != uint64_int32[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // uint64_int32[i].x, uint64_int32[i].y, uint64_int32[i].fExpected ? "true" : "false");
            cerr << "Error in case uint64_int32: ";
            cerr << hex << setw(16) << setfill('0') << uint64_int32[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint64_int32[i].y << ", ";
            cerr << "expected = " << uint64_int32[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<unsigned __int64> si(uint64_int32[i].x);
            si *= uint64_int32[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != uint64_int32[i].fExpected )
          {
            // printf("Error in case uint64_int32 throw: %I64X, %I64X, expected = %s\n",
            // uint64_int32[i].x, uint64_int32[i].y, uint64_int32[i].fExpected ? "true" : "false");
            cerr << "Error in case uint64_int32 throw: ";
            cerr << hex << setw(16) << setfill('0') << uint64_int32[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << uint64_int32[i].y << ", ";
            cerr << "expected = " << uint64_int32[i].fExpected << endl;
          }
      }
  }

  static const MultTest< __int64, __int64 > int64_int64[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffffLL,            0LL, true },
      { 0x80000000LL,            0LL, true },
      { 0xffffffffLL,            0LL, true },
      { 0x100000000LL,           0LL, true },
      { 0x200000000LL,           0LL, true },
      { 0x7fffffffffffffffLL,    0LL, true },
      { 0x8000000000000000LL,    0LL, true },
      { 0xffffffffffffffffLL,    0LL, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffffLL,            1LL, true },
      { 0x80000000LL,            1LL, true },
      { 0xffffffffLL,            1LL, true },
      { 0x100000000LL,           1LL, true },
      { 0x200000000LL,           1LL, true },
      { 0x7fffffffffffffffLL,    1LL, true },
      { 0x8000000000000000LL,    1LL, true },
      { 0xffffffffffffffffLL,    1LL, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffffLL,            2LL, true },
      { 0x80000000LL,            2LL, true },
      { 0xffffffffLL,            2LL, true },
      { 0x100000000LL,           2LL, true },
      { 0x200000000LL,           2LL, true },
      { 0x7fffffffffffffffLL,    2LL, false },
      { 0x8000000000000000LL,    2LL, false },
      { 0xffffffffffffffffLL,    2LL, true },
      { 0LL,                     0x7fffffffLL, true },
      { 1LL,                     0x7fffffffLL, true },
      { 2LL,                     0x7fffffffLL, true },
      { 0x7fffffffLL,            0x7fffffffLL, true },
      { 0x80000000LL,            0x7fffffffLL, true },
      { 0xffffffffLL,            0x7fffffffLL, true },
      { 0x100000000LL,           0x7fffffffLL, true },
      { 0x200000000LL,           0x7fffffffLL, false },
      { 0x7fffffffffffffffLL,    0x7fffffffLL, false },
      { 0x8000000000000000LL,    0x7fffffffLL, false },
      { 0xffffffffffffffffLL,    0x7fffffffLL, true },
      { 0LL,                     0x80000000LL, true },
      { 1LL,                     0x80000000LL, true },
      { 2LL,                     0x80000000LL, true },
      { 0x7fffffffLL,            0x80000000LL, true },
      { 0x80000000LL,            0x80000000LL, true },
      { 0xffffffffLL,            0x80000000LL, true },
      { 0x100000000LL,           0x80000000LL, false },
      { 0x200000000LL,           0x80000000LL, false },
      { 0x7fffffffffffffffLL,    0x80000000LL, false },
      { 0x8000000000000000LL,    0x80000000LL, false },
      { 0xffffffffffffffffLL,    0x80000000LL, true },
      { 0LL,                     0xffffffffLL, true },
      { 1LL,                     0xffffffffLL, true },
      { 2LL,                     0xffffffffLL, true },
      { 0x7fffffffLL,            0xffffffffLL, true },
      { 0x80000000LL,            0xffffffffLL, true },
      { 0xffffffffLL,            0xffffffffLL, false },
      { 0x100000000LL,           0xffffffffLL, false },
      { 0x200000000LL,           0xffffffffLL, false },
      { 0x7fffffffffffffffLL,    0xffffffffLL, false },
      { 0x8000000000000000LL,    0xffffffffLL, false },
      { 0xffffffffffffffffLL,    0xffffffffLL, true },
      { 0LL,                     0x100000000LL, true },
      { 1LL,                     0x100000000LL, true },
      { 2LL,                     0x100000000LL, true },
      { 0x7fffffffLL,            0x100000000LL, true },
      { 0x80000000LL,            0x100000000LL, false },
      { 0xffffffffLL,            0x100000000LL, false },
      { 0x100000000LL,           0x100000000LL, false },
      { 0x200000000LL,           0x100000000LL, false },
      { 0x7fffffffffffffffLL,    0x100000000LL, false },
      { 0x8000000000000000LL,    0x100000000LL, false },
      { 0xffffffffffffffffLL,    0x100000000LL, true },
      { 0LL,                     0x200000000LL, true },
      { 1LL,                     0x200000000LL, true },
      { 2LL,                     0x200000000LL, true },
      { 0x7fffffffLL,            0x200000000LL, false },
      { 0x80000000LL,            0x200000000LL, false },
      { 0xffffffffLL,            0x200000000LL, false },
      { 0x100000000LL,           0x200000000LL, false },
      { 0x200000000LL,           0x200000000LL, false },
      { 0x7fffffffffffffffLL,    0x200000000LL, false },
      { 0x8000000000000000LL,    0x200000000LL, false },
      { 0xffffffffffffffffLL,    0x200000000LL, true },
      { 0LL,                     0x7fffffffffffffffLL, true },
      { 1LL,                     0x7fffffffffffffffLL, true },
      { 2LL,                     0x7fffffffffffffffLL, false },
      { 0x7fffffffLL,            0x7fffffffffffffffLL, false },
      { 0x80000000LL,            0x7fffffffffffffffLL, false },
      { 0xffffffffLL,            0x7fffffffffffffffLL, false },
      { 0x100000000LL,           0x7fffffffffffffffLL, false },
      { 0x200000000LL,           0x7fffffffffffffffLL, false },
      { 0x7fffffffffffffffLL,    0x7fffffffffffffffLL, false },
      { 0x8000000000000000LL,    0x7fffffffffffffffLL, false },
      { 0xffffffffffffffffLL,    0x7fffffffffffffffLL, true },
      { 0LL,                     0x8000000000000000LL, true },
      { 1LL,                     0x8000000000000000LL, true },
      { 2LL,                     0x8000000000000000LL, false },
      { 0x7fffffffLL,            0x8000000000000000LL, false },
      { 0x80000000LL,            0x8000000000000000LL, false },
      { 0xffffffffLL,            0x8000000000000000LL, false },
      { 0x100000000LL,           0x8000000000000000LL, false },
      { 0x200000000LL,           0x8000000000000000LL, false },
      { 0x7fffffffffffffffLL,    0x8000000000000000LL, false },
      { 0x8000000000000000LL,    0x8000000000000000LL, false },
      { 0xffffffffffffffffLL,    0x8000000000000000LL, false },
      { 0LL,                     0xffffffffffffffffLL, true },
      { 1LL,                     0xffffffffffffffffLL, true },
      { 2LL,                     0xffffffffffffffffLL, true },
      { 0x7fffffffLL,            0xffffffffffffffffLL, true },
      { 0x80000000LL,            0xffffffffffffffffLL, true },
      { 0xffffffffLL,            0xffffffffffffffffLL, true },
      { 0x100000000LL,           0xffffffffffffffffLL, true },
      { 0x200000000LL,           0xffffffffffffffffLL, true },
      { 0x7fffffffffffffffLL,    0xffffffffffffffffLL, true },
      { 0x8000000000000000LL,    0xffffffffffffffffLL, false },
      { 0xffffffffffffffffLL,    0xffffffffffffffffLL, true },
      // Special case - force addition overflow case
      { 0xffffffffLL,            0x100000002LL, false }
    };

  void MultVerifyInt64Int64()
  {
    size_t i;

    for( i = 0; i < COUNTOF(int64_int64); ++i )
      {
        __int64 ret;
        if( SafeMultiply(int64_int64[i].x, int64_int64[i].y, ret) != int64_int64[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // int64_int64[i].x, int64_int64[i].y, int64_int64[i].fExpected ? "true" : "false");
            cerr << "Error in case int64_int64: ";
            cerr << hex << setw(16) << setfill('0') << int64_int64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int64_int64[i].y << ", ";
            cerr << "expected = " << int64_int64[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<signed __int64> si(int64_int64[i].x);
            si *= int64_int64[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != int64_int64[i].fExpected )
          {
            // printf("Error in case int64_int64 throw: %I64X, %I64X, expected = %s\n",
            // int64_int64[i].x, int64_int64[i].y, int64_int64[i].fExpected ? "true" : "false");
            cerr << "Error in case int64_int64 throw: ";
            cerr << hex << setw(16) << setfill('0') << int64_int64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int64_int64[i].y << ", ";
            cerr << "expected = " << int64_int64[i].fExpected << endl;
          }
      }
  }

  static const MultTest< __int64, unsigned __int64 > int64_uint64[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffffLL,            0ULL, true },
      { 0x80000000LL,            0ULL, true },
      { 0xffffffffLL,            0ULL, true },
      { 0x100000000LL,           0ULL, true },
      { 0x200000000LL,           0ULL, true },
      { 0x7fffffffffffffffLL,    0ULL, true },
      { 0x8000000000000000LL,    0ULL, true },
      { 0xffffffffffffffffLL,    0ULL, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffffLL,            1ULL, true },
      { 0x80000000LL,            1ULL, true },
      { 0xffffffffLL,            1ULL, true },
      { 0x100000000LL,           1ULL, true },
      { 0x200000000LL,           1ULL, true },
      { 0x7fffffffffffffffLL,    1ULL, true },
      { 0x8000000000000000LL,    1ULL, true },
      { 0xffffffffffffffffLL,    1ULL, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffffLL,            2ULL, true },
      { 0x80000000LL,            2ULL, true },
      { 0xffffffffLL,            2ULL, true },
      { 0x100000000LL,           2ULL, true },
      { 0x200000000LL,           2ULL, true },
      { 0x7fffffffffffffffLL,    2ULL, false },
      { 0x8000000000000000LL,    2ULL, false },
      { 0xffffffffffffffffLL,    2ULL, true },
      { 0LL,                     0x7fffffffULL, true },
      { 1LL,                     0x7fffffffULL, true },
      { 2LL,                     0x7fffffffULL, true },
      { 0x7fffffffLL,            0x7fffffffULL, true },
      { 0x80000000LL,            0x7fffffffULL, true },
      { 0xffffffffLL,            0x7fffffffULL, true },
      { 0x100000000LL,           0x7fffffffULL, true },
      { 0x200000000LL,           0x7fffffffULL, false },
      { 0x7fffffffffffffffLL,    0x7fffffffULL, false },
      { 0x8000000000000000LL,    0x7fffffffULL, false },
      { 0xffffffffffffffffLL,    0x7fffffffULL, true },
      { 0LL,                     0x80000000ULL, true },
      { 1LL,                     0x80000000ULL, true },
      { 2LL,                     0x80000000ULL, true },
      { 0x7fffffffLL,            0x80000000ULL, true },
      { 0x80000000LL,            0x80000000ULL, true },
      { 0xffffffffLL,            0x80000000ULL, true },
      { 0x100000000LL,           0x80000000ULL, false },
      { 0x200000000LL,           0x80000000ULL, false },
      { 0x7fffffffffffffffLL,    0x80000000ULL, false },
      { 0x8000000000000000LL,    0x80000000ULL, false },
      { 0xffffffffffffffffLL,    0x80000000ULL, true },
      { 0LL,                     0xffffffffULL, true },
      { 1LL,                     0xffffffffULL, true },
      { 2LL,                     0xffffffffULL, true },
      { 0x7fffffffLL,            0xffffffffULL, true },
      { 0x80000000LL,            0xffffffffULL, true },
      { 0xffffffffLL,            0xffffffffULL, false },
      { 0x100000000LL,           0xffffffffULL, false },
      { 0x200000000LL,           0xffffffffULL, false },
      { 0x7fffffffffffffffLL,    0xffffffffULL, false },
      { 0x8000000000000000LL,    0xffffffffULL, false },
      { 0xffffffffffffffffLL,    0xffffffffULL, true },
      { 0LL,                     0x100000000ULL, true },
      { 1LL,                     0x100000000ULL, true },
      { 2LL,                     0x100000000ULL, true },
      { 0x7fffffffLL,            0x100000000ULL, true },
      { 0x80000000LL,            0x100000000ULL, false },
      { 0xffffffffLL,            0x100000000ULL, false },
      { 0x100000000LL,           0x100000000ULL, false },
      { 0x200000000LL,           0x100000000ULL, false },
      { 0x7fffffffffffffffLL,    0x100000000ULL, false },
      { 0x8000000000000000LL,    0x100000000ULL, false },
      { 0xffffffffffffffffLL,    0x100000000ULL, true },
      { 0LL,                     0x200000000ULL, true },
      { 1LL,                     0x200000000ULL, true },
      { 2LL,                     0x200000000ULL, true },
      { 0x7fffffffLL,            0x200000000ULL, false },
      { 0x80000000LL,            0x200000000ULL, false },
      { 0xffffffffLL,            0x200000000ULL, false },
      { 0x100000000LL,           0x200000000ULL, false },
      { 0x200000000LL,           0x200000000ULL, false },
      { 0x7fffffffffffffffLL,    0x200000000ULL, false },
      { 0x8000000000000000LL,    0x200000000ULL, false },
      { 0xffffffffffffffffLL,    0x200000000ULL, true },
      { 0LL,                     0x7fffffffffffffffULL, true },
      { 1LL,                     0x7fffffffffffffffULL, true },
      { 2LL,                     0x7fffffffffffffffULL, false },
      { 0x7fffffffLL,            0x7fffffffffffffffULL, false },
      { 0x80000000LL,            0x7fffffffffffffffULL, false },
      { 0xffffffffLL,            0x7fffffffffffffffULL, false },
      { 0x100000000LL,           0x7fffffffffffffffULL, false },
      { 0x200000000LL,           0x7fffffffffffffffULL, false },
      { 0x7fffffffffffffffLL,    0x7fffffffffffffffULL, false },
      { 0x8000000000000000LL,    0x7fffffffffffffffULL, false },
      { 0xffffffffffffffffLL,    0x7fffffffffffffffULL, true },
      { 0LL,                     0x8000000000000000ULL, true },
      { 1LL,                     0x8000000000000000ULL, false },
      { 2LL,                     0x8000000000000000ULL, false },
      { 0x7fffffffLL,            0x8000000000000000ULL, false },
      { 0x80000000LL,            0x8000000000000000ULL, false },
      { 0xffffffffLL,            0x8000000000000000ULL, false },
      { 0x100000000LL,           0x8000000000000000ULL, false },
      { 0x200000000LL,           0x8000000000000000ULL, false },
      { 0x7fffffffffffffffLL,    0x8000000000000000ULL, false },
      { 0x8000000000000000LL,    0x8000000000000000ULL, false },
      { 0xffffffffffffffffLL,    0x8000000000000000ULL, true },
      { 0LL,                     0xffffffffffffffffULL, true },
      { 1LL,                     0xffffffffffffffffULL, false },
      { 2LL,                     0xffffffffffffffffULL, false },
      { 0x7fffffffLL,            0xffffffffffffffffULL, false },
      { 0x80000000LL,            0xffffffffffffffffULL, false },
      { 0xffffffffLL,            0xffffffffffffffffULL, false },
      { 0x100000000LL,           0xffffffffffffffffULL, false },
      { 0x200000000LL,           0xffffffffffffffffULL, false },
      { 0x7fffffffffffffffLL,    0xffffffffffffffffULL, false },
      { 0x8000000000000000LL,    0xffffffffffffffffULL, false },
      { 0xffffffffffffffffLL,    0xffffffffffffffffULL, false },
      // Special case - force addition overflow case
      { 0xffffffffLL,            0x100000002ULL, false }
    };

  void MultVerifyInt64Uint64()
  {
    size_t i;

    for( i = 0; i < COUNTOF(int64_uint64); ++i )
      {
        __int64 ret;
        if( SafeMultiply(int64_uint64[i].x, int64_uint64[i].y, ret) != int64_uint64[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // int64_uint64[i].x, int64_uint64[i].y, int64_uint64[i].fExpected ? "true" : "false");
            cerr << "Error in case int64_uint64: ";
            cerr << hex << setw(16) << setfill('0') << int64_uint64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int64_uint64[i].y << ", ";
            cerr << "expected = " << int64_uint64[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<signed __int64> si(int64_uint64[i].x);
            si *= int64_uint64[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != int64_uint64[i].fExpected )
          {
            // printf("Error in case int64_uint64 throw: %I64X, %I64X, expected = %s\n",
            // int64_uint64[i].x, int64_uint64[i].y, int64_uint64[i].fExpected ? "true" : "false");
            cerr << "Error in case int64_uint64 throw: ";
            cerr << hex << setw(16) << setfill('0') << int64_uint64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int64_uint64[i].y << ", ";
            cerr << "expected = " << int64_uint64[i].fExpected << endl;
          }
      }
  }

  static const MultTest< __int64, __int32 > int64_int[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffffLL,            0, true },
      { 0x80000000LL,            0, true },
      { 0xffffffffLL,            0, true },
      { 0x100000000LL,           0, true },
      { 0x200000000LL,           0, true },
      { 0x7fffffffffffffffLL,    0, true },
      { 0x8000000000000000LL,    0, true },
      { 0xffffffffffffffffLL,    0, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffffLL,            1, true },
      { 0x80000000LL,            1, true },
      { 0xffffffffLL,            1, true },
      { 0x100000000LL,           1, true },
      { 0x200000000LL,           1, true },
      { 0x7fffffffffffffffLL,    1, true },
      { 0x8000000000000000LL,    1, true },
      { 0xffffffffffffffffLL,    1, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffffLL,            2, true },
      { 0x80000000LL,            2, true },
      { 0xffffffffLL,            2, true },
      { 0x100000000LL,           2, true },
      { 0x200000000LL,           2, true },
      { 0x7fffffffffffffffLL,    2, false },
      { 0x8000000000000000LL,    2, false },
      { 0xffffffffffffffffLL,    2, true },
      { 0LL,                     0x7fffffff, true },
      { 1LL,                     0x7fffffff, true },
      { 2LL,                     0x7fffffff, true },
      { 0x7fffffffLL,            0x7fffffff, true },
      { 0x80000000LL,            0x7fffffff, true },
      { 0xffffffffLL,            0x7fffffff, true },
      { 0x100000000LL,           0x7fffffff, true },
      { 0x200000000LL,           0x7fffffff, false },
      { 0x7fffffffffffffffLL,    0x7fffffff, false },
      { 0x8000000000000000LL,    0x7fffffff, false },
      { 0xffffffffffffffffLL,    0x7fffffff, true },
      { 0LL,                     0x80000000, true },
      { 1LL,                     0x80000000, true },
      { 2LL,                     0x80000000, true },
      { 0x7fffffffLL,            0x80000000, true },
      { 0x80000000LL,            0x80000000, true },
      { 0xffffffffLL,            0x80000000, true },
      { 0x100000000LL,           0x80000000, true },
      { 0x200000000LL,           0x80000000, false },
      { 0x7fffffffffffffffLL,    0x80000000, false },
      { 0x8000000000000000LL,    0x80000000, false },
      { 0xffffffffffffffffLL,    0x80000000, true },
      { 0LL,                     0xffffffff, true },
      { 1LL,                     0xffffffff, true },
      { 2LL,                     0xffffffff, true },
      { 0x7fffffffLL,            0xffffffff, true },
      { 0x80000000LL,            0xffffffff, true },
      { 0xffffffffLL,            0xffffffff, true },
      { 0x100000000LL,           0xffffffff, true },
      { 0x200000000LL,           0xffffffff, true },
      { 0x7fffffffffffffffLL,    0xffffffff, true },
      { 0x8000000000000000LL,    0xffffffff, false },
      { 0xffffffffffffffffLL,    0xffffffff, true }
    };

  void MultVerifyInt64Int()
  {
    size_t i;

    for( i = 0; i < COUNTOF(int64_int); ++i )
      {
        __int64 ret;
        if( SafeMultiply(int64_int[i].x, int64_int[i].y, ret) != int64_int[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // int64_int[i].x, int64_int[i].y, int64_int[i].fExpected ? "true" : "false");
            cerr << "Error in case int64_int: ";
            cerr << hex << setw(16) << setfill('0') << int64_int[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int64_int[i].y << ", ";
            cerr << "expected = " << int64_int[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<signed __int64> si(int64_int[i].x);
            si *= int64_int[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != int64_int[i].fExpected )
          {
            // printf("Error in case int64_int throw: %I64X, %I64X, expected = %s\n",
            // int64_int[i].x, int64_int[i].y, int64_int[i].fExpected ? "true" : "false");
            cerr << "Error in case int64_int throw: ";
            cerr << hex << setw(16) << setfill('0') << int64_int[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int64_int[i].y << ", ";
            cerr << "expected = " << int64_int[i].fExpected << endl;
          }
      }
  }

  static const MultTest< __int64, unsigned __int32 > int64_uint[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffffLL,            0, true },
      { 0x80000000LL,            0, true },
      { 0xffffffffLL,            0, true },
      { 0x100000000LL,           0, true },
      { 0x200000000LL,           0, true },
      { 0x7fffffffffffffffLL,    0, true },
      { 0x8000000000000000LL,    0, true },
      { 0xffffffffffffffffLL,    0, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffffLL,            1, true },
      { 0x80000000LL,            1, true },
      { 0xffffffffLL,            1, true },
      { 0x100000000LL,           1, true },
      { 0x200000000LL,           1, true },
      { 0x7fffffffffffffffLL,    1, true },
      { 0x8000000000000000LL,    1, true },
      { 0xffffffffffffffffLL,    1, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffffLL,            2, true },
      { 0x80000000LL,            2, true },
      { 0xffffffffLL,            2, true },
      { 0x100000000LL,           2, true },
      { 0x200000000LL,           2, true },
      { 0x7fffffffffffffffLL,    2, false },
      { 0x8000000000000000LL,    2, false },
      { 0xffffffffffffffffLL,    2, true },
      { 0LL,                     0x7fffffff, true },
      { 1LL,                     0x7fffffff, true },
      { 2LL,                     0x7fffffff, true },
      { 0x7fffffffLL,            0x7fffffff, true },
      { 0x80000000LL,            0x7fffffff, true },
      { 0xffffffffLL,            0x7fffffff, true },
      { 0x100000000LL,           0x7fffffff, true },
      { 0x200000000LL,           0x7fffffff, false },
      { 0x7fffffffffffffffLL,    0x7fffffff, false },
      { 0x8000000000000000LL,    0x7fffffff, false },
      { 0xffffffffffffffffLL,    0x7fffffff, true },
      { 0LL,                     0x80000000, true },
      { 1LL,                     0x80000000, true },
      { 2LL,                     0x80000000, true },
      { 0x7fffffffLL,            0x80000000, true },
      { 0x80000000LL,            0x80000000, true },
      { 0xffffffffLL,            0x80000000, true },
      { 0x100000000LL,           0x80000000, false },
      { 0x200000000LL,           0x80000000, false },
      { 0x7fffffffffffffffLL,    0x80000000, false },
      { 0x8000000000000000LL,    0x80000000, false },
      { 0xffffffffffffffffLL,    0x80000000, true },
      { 0LL,                     0xffffffff, true },
      { 1LL,                     0xffffffff, true },
      { 2LL,                     0xffffffff, true },
      { 0x7fffffffLL,            0xffffffff, true },
      { 0x80000000LL,            0xffffffff, true },
      { 0xffffffffLL,            0xffffffff, false },
      { 0x100000000LL,           0xffffffff, false },
      { 0x200000000LL,           0xffffffff, false },
      { 0x7fffffffffffffffLL,    0xffffffff, false },
      { 0x8000000000000000LL,    0xffffffff, false },
      { 0xffffffffffffffffLL,    0xffffffff, true }
    };

  void MultVerifyInt64Uint()
  {
    size_t i;

    for( i = 0; i < COUNTOF(int64_uint); ++i )
      {
        __int64 ret;
        if( SafeMultiply(int64_uint[i].x, int64_uint[i].y, ret) != int64_uint[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // int64_uint[i].x, int64_uint[i].y, int64_uint[i].fExpected ? "true" : "false");
            cerr << "Error in case int64_uint: ";
            cerr << hex << setw(16) << setfill('0') << int64_uint[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int64_uint[i].y << ", ";
            cerr << "expected = " << int64_uint[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<signed __int64> si(int64_uint[i].x);
            si *= int64_uint[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != int64_uint[i].fExpected )
          {
            // printf("Error in case int64_uint throw: %I64X, %I64X, expected = %s\n",
            // int64_uint[i].x, int64_uint[i].y, int64_uint[i].fExpected ? "true" : "false");
            cerr << "Error in case int64_uint throw: ";
            cerr << hex << setw(16) << setfill('0') << int64_uint[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int64_uint[i].y << ", ";
            cerr << "expected = " << int64_uint[i].fExpected << endl;
          }
      }
  }

  static const MultTest< __int32, __int64 > int_int64[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffff,            0LL, true },
      { 0x80000000,            0LL, true },
      { 0xffffffff,            0LL, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffff,            1LL, true },
      { 0x80000000,            1LL, true },
      { 0xffffffff,            1LL, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffff,            2LL, false },
      { 0x80000000,            2LL, false },
      { 0xffffffff,            2LL, true },
      { 0,                     0x7fffffffLL, true },
      { 1,                     0x7fffffffLL, true },
      { 2,                     0x7fffffffLL, false },
      { 0x7fffffff,            0x7fffffffLL, false },
      { 0x80000000,            0x7fffffffLL, false },
      { 0xffffffff,            0x7fffffffLL, true },
      { 0,                     0x80000000LL, true },
      { 1,                     0x80000000LL, false },
      { 2,                     0x80000000LL, false },
      { 0x7fffffff,            0x80000000LL, false },
      { 0x80000000,            0x80000000LL, false },
      { 0xffffffff,            0x80000000LL, true },
      { 0,                     0xffffffffLL, true },
      { 1,                     0xffffffffLL, false },
      { 2,                     0xffffffffLL, false },
      { 0x7fffffff,            0xffffffffLL, false },
      { 0x80000000,            0xffffffffLL, false },
      { 0xffffffff,            0xffffffffLL, false },
      { 0,                     0x100000000LL, true },
      { 1,                     0x100000000LL, false },
      { 2,                     0x100000000LL, false },
      { 0x7fffffff,            0x100000000LL, false },
      { 0x80000000,            0x100000000LL, false },
      { 0xffffffff,            0x100000000LL, false },
      { 0,                     0x200000000LL, true },
      { 1,                     0x200000000LL, false },
      { 2,                     0x200000000LL, false },
      { 0x7fffffff,            0x200000000LL, false },
      { 0x80000000,            0x200000000LL, false },
      { 0xffffffff,            0x200000000LL, false },
      { 0,                     0x7fffffffffffffffLL, true },
      { 1,                     0x7fffffffffffffffLL, false },
      { 2,                     0x7fffffffffffffffLL, false },
      { 0x7fffffff,            0x7fffffffffffffffLL, false },
      { 0x80000000,            0x7fffffffffffffffLL, false },
      { 0xffffffff,            0x7fffffffffffffffLL, false },
      { 0,                     0x8000000000000000LL, true },
      { 1,                     0x8000000000000000LL, false },
      { 2,                     0x8000000000000000LL, false },
      { 0x7fffffff,            0x8000000000000000LL, false },
      { 0x80000000,            0x8000000000000000LL, false },
      { 0xffffffff,            0x8000000000000000LL, false },
      { 0,                     0xffffffffffffffffLL, true },
      { 1,                     0xffffffffffffffffLL, true },
      { 2,                     0xffffffffffffffffLL, true },
      { 0x7fffffff,            0xffffffffffffffffLL, true },
      { 0x80000000,            0xffffffffffffffffLL, false },
      { 0xffffffff,            0xffffffffffffffffLL, true },
      // Special case - force addition overflow case
      { 0xffffffff,            0x100000002LL, false }
    };

  void MultVerifyIntInt64()
  {
    size_t i;

    for( i = 0; i < COUNTOF(int_int64); ++i )
      {
        __int32 ret;
        if( SafeMultiply(int_int64[i].x, int_int64[i].y, ret) != int_int64[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // int_int64[i].x, int_int64[i].y, int_int64[i].fExpected ? "true" : "false");
            cerr << "Error in case int_int64: ";
            cerr << hex << setw(16) << setfill('0') << int_int64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int_int64[i].y << ", ";
            cerr << "expected = " << int_int64[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<signed __int32> si(int_int64[i].x);
            si *= int_int64[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != int_int64[i].fExpected )
          {
            // printf("Error in case int_int64 throw: %I64X, %I64X, expected = %s\n",
            // int_int64[i].x, int_int64[i].y, int_int64[i].fExpected ? "true" : "false");
            cerr << "Error in case int_int64 throw: ";
            cerr << hex << setw(16) << setfill('0') << int_int64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int_int64[i].y << ", ";
            cerr << "expected = " << int_int64[i].fExpected << endl;
          }
      }
  }

  static const MultTest< __int32, unsigned __int64 > int_uint64[] = 
    {
      { 0,                     0, true },
      { 1,                     0, true },
      { 2,                     0, true },
      { 0x7fffffff,            0ULL, true },
      { 0x80000000,            0ULL, true },
      { 0xffffffff,            0ULL, true },
      { 0,                     1, true },
      { 1,                     1, true },
      { 2,                     1, true },
      { 0x7fffffff,            1ULL, true },
      { 0x80000000,            1ULL, true },
      { 0xffffffff,            1ULL, true },
      { 0,                     2, true },
      { 1,                     2, true },
      { 2,                     2, true },
      { 0x7fffffff,            2ULL, false },
      { 0x80000000,            2ULL, false },
      { 0xffffffff,            2ULL, true },
      { 0,                     0x7fffffffULL, true },
      { 1,                     0x7fffffffULL, true },
      { 2,                     0x7fffffffULL, false },
      { 0x7fffffff,            0x7fffffffULL, false },
      { 0x80000000,            0x7fffffffULL, false },
      { 0xffffffff,            0x7fffffffULL, true },
      { 0,                     0x80000000ULL, true },
      { 1,                     0x80000000ULL, false },
      { 2,                     0x80000000ULL, false },
      { 0x7fffffff,            0x80000000ULL, false },
      { 0x80000000,            0x80000000ULL, false },
      { 0xffffffff,            0x80000000ULL, true },
      { 0,                     0xffffffffULL, true },
      { 1,                     0xffffffffULL, false },
      { 2,                     0xffffffffULL, false },
      { 0x7fffffff,            0xffffffffULL, false },
      { 0x80000000,            0xffffffffULL, false },
      { 0xffffffff,            0xffffffffULL, false },
      { 0,                     0x100000000ULL, true },
      { 1,                     0x100000000ULL, false },
      { 2,                     0x100000000ULL, false },
      { 0x7fffffff,            0x100000000ULL, false },
      { 0x80000000,            0x100000000ULL, false },
      { 0xffffffff,            0x100000000ULL, false },
      { 0,                     0x200000000ULL, true },
      { 1,                     0x200000000ULL, false },
      { 2,                     0x200000000ULL, false },
      { 0x7fffffff,            0x200000000ULL, false },
      { 0x80000000,            0x200000000ULL, false },
      { 0xffffffff,            0x200000000ULL, false },
      { 0,                     0x7fffffffffffffffULL, true },
      { 1,                     0x7fffffffffffffffULL, false },
      { 2,                     0x7fffffffffffffffULL, false },
      { 0x7fffffff,            0x7fffffffffffffffULL, false },
      { 0x80000000,            0x7fffffffffffffffULL, false },
      { 0xffffffff,            0x7fffffffffffffffULL, false },
      { 0,                     0x8000000000000000ULL, true },
      { 1,                     0x8000000000000000ULL, false },
      { 2,                     0x8000000000000000ULL, false },
      { 0x7fffffff,            0x8000000000000000ULL, false },
      { 0x80000000,            0x8000000000000000ULL, false },
      { 0xffffffff,            0x8000000000000000ULL, false },
      { 0,                     0xffffffffffffffffULL, true },
      { 1,                     0xffffffffffffffffULL, false },
      { 2,                     0xffffffffffffffffULL, false },
      { 0x7fffffff,            0xffffffffffffffffULL, false },
      { 0x80000000,            0xffffffffffffffffULL, false },
      { 0xffffffff,            0xffffffffffffffffULL, false },
      // Special case - force addition overflow case
      { 0xffffffff,            0x100000002ULL, false }
    };

  void MultVerifyIntUint64()
  {
    size_t i;

    for( i = 0; i < COUNTOF(int_uint64); ++i )
      {
        __int32 ret;
        if( SafeMultiply(int_uint64[i].x, int_uint64[i].y, ret) != int_uint64[i].fExpected )
          {
            //assert(false);
            // printf("Error in case %I64X, %I64X, expected = %s\n",
            // int_uint64[i].x, int_uint64[i].y, int_uint64[i].fExpected ? "true" : "false");
            cerr << "Error in case int_uint64: ";
            cerr << hex << setw(16) << setfill('0') << int_uint64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int_uint64[i].y << ", ";
            cerr << "expected = " << int_uint64[i].fExpected << endl;
          }

        bool fSuccess = true;
        try
          {
            SafeInt<signed __int32> si(int_uint64[i].x);
            si *= int_uint64[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != int_uint64[i].fExpected )
          {
            // printf("Error in case int_uint64 throw: %I64X, %I64X, expected = %s\n",
            // int_uint64[i].x, int_uint64[i].y, int_uint64[i].fExpected ? "true" : "false");
            cerr << "Error in case int_uint64 throw: ";
            cerr << hex << setw(16) << setfill('0') << int_uint64[i].x << ", ";
            cerr << hex << setw(16) << setfill('0') << int_uint64[i].y << ", ";
            cerr << "expected = " << int_uint64[i].fExpected << endl;
          }
      }
  }

  static const MultTest< unsigned __int8, unsigned __int8 > uint8_uint8[] = 
    {
      { 0,      0, true },
      { 1,      0, true },
      { 2,      0, true },
      { 4,      0, true },
      { 0x10,   0ULL, true },
      { 0x20,   0ULL, true },
      { 0x7f,   0ULL, true },
      { 0x80,   0ULL, true },
      { 0xc0,   0ULL, true },
      { 0xe0,   0ULL, true },
      { 0xff,   0ULL, true },

      { 0,      1, true },
      { 1,      1, true },
      { 2,      1, true },
      { 4,      1, true },
      { 0x10,   1ULL, true },
      { 0x20,   1ULL, true },
      { 0x7f,   1ULL, true },
      { 0x80,   1ULL, true },
      { 0xc0,   1ULL, true },
      { 0xe0,   1ULL, true },
      { 0xff,   1ULL, true },

      { 0,      2, true },
      { 1,      2, true },
      { 2,      2, true },
      { 4,      2, true },
      { 0x10,   2ULL, true },
      { 0x20,   2ULL, true },
      { 0x7f,   2ULL, true },
      { 0x80,   2ULL, false },
      { 0xc0,   2ULL, false },
      { 0xe0,   2ULL, false },
      { 0xff,   2ULL, false },

      { 0,      4, true },
      { 1,      4, true },
      { 2,      4, true },
      { 4,      4, true },
      { 0x10,   4ULL, true },
      { 0x20,   4ULL, true },
      { 0x3f,   4ULL, true },
      { 0x40,   4ULL, false },
      { 0x7f,   4ULL, false },
      { 0x80,   4ULL, false },
      { 0xc0,   4ULL, false },
      { 0xe0,   4ULL, false },
      { 0xff,   4ULL, false },

      { 0,      0x10ULL, true },
      { 1,      0x10ULL, true },
      { 2,      0x10ULL, true },
      { 4,      0x10ULL, true },
      { 0x0f,   0x10ULL, true },
      { 0x10,   0x10ULL, false },
      { 0x20,   0x10ULL, false },
      { 0x7f,   0x10ULL, false },
      { 0x80,   0x10ULL, false },
      { 0xc0,   0x10ULL, false },
      { 0xe0,   0x10ULL, false },
      { 0xff,   0x10ULL, false },

      { 0,      0x20ULL, true },
      { 1,      0x20ULL, true },
      { 2,      0x20ULL, true },
      { 4,      0x20ULL, true },
      { 7,      0x20ULL, true },
      { 0x10,   0x20ULL, false },
      { 0x20,   0x20ULL, false },
      { 0x7f,   0x20ULL, false },
      { 0x80,   0x20ULL, false },
      { 0xc0,   0x20ULL, false },
      { 0xe0,   0x20ULL, false },
      { 0xff,   0x20ULL, false },

      { 0,      0x7fULL, true },
      { 1,      0x7fULL, true },
      { 2,      0x7fULL, true },
      { 4,      0x7fULL, false },
      { 0x10,   0x7fULL, false },
      { 0x20,   0x7fULL, false },
      { 0x7f,   0x7fULL, false },
      { 0x80,   0x7fULL, false },
      { 0xc0,   0x7fULL, false },
      { 0xe0,   0x7fULL, false },
      { 0xff,   0x7fULL, false },

      { 0,      0x40ULL, true },
      { 1,      0x40ULL, true },
      { 2,      0x40ULL, true },
      { 3,      0x40ULL, true },
      { 4,      0x40ULL, false },
      { 0x10,   0x40ULL, false },
      { 0x20,   0x40ULL, false },
      { 0x7f,   0x40ULL, false },
      { 0x80,   0x40ULL, false },
      { 0xc0,   0x40ULL, false },
      { 0xe0,   0x40ULL, false },
      { 0xff,   0x40ULL, false },

      { 0,      0x80ULL, true },
      { 1,      0x80ULL, true },
      { 2,      0x80ULL, false },
      { 4,      0x80ULL, false },
      { 0x10,   0x80ULL, false },
      { 0x20,   0x80ULL, false },
      { 0x7f,   0x80ULL, false },
      { 0x80,   0x80ULL, false },
      { 0xc0,   0x80ULL, false },
      { 0xe0,   0x80ULL, false },
      { 0xff,   0x80ULL, false },

      { 0,      0xffULL, true },
      { 1,      0xffULL, true },
      { 2,      0xffULL, false },
      { 4,      0xffULL, false },
      { 0x10,   0xffULL, false },
      { 0x20,   0xffULL, false },
      { 0x7f,   0xffULL, false },
      { 0x80,   0xffULL, false },
      { 0xc0,   0xffULL, false },
      { 0xe0,   0xffULL, false },
      { 0xff,   0xffULL, false },
    };

  void MultVerifyUint8Uint8()
  {
    size_t i;

    for( i = 0; i < COUNTOF(uint8_uint8); ++i )
      {
        unsigned __int8 ret;
        if( SafeMultiply(uint8_uint8[i].x, uint8_uint8[i].y, ret) != uint8_uint8[i].fExpected )
          {
            //assert(false);
            // printf("Error in case uint8_uint8: %02X, %02X, expected = %s\n",
            // uint8_uint8[i].x, uint8_uint8[i].y, uint8_uint8[i].fExpected ? "true" : "false");
            cerr << "Error in case uint8_uint8: ";
            cerr << hex << setw(2) << setfill('0') << (unsigned int)uint8_uint8[i].x << ", ";
            cerr << hex << setw(2) << setfill('0') << (unsigned int)uint8_uint8[i].y << ", ";
            cerr << "expected = " << uint8_uint8[i].fExpected << endl;
          }

        // Now test throwing version
        bool fSuccess = true;
        try
          {
            SafeInt<unsigned __int8> si(uint8_uint8[i].x);
            si *= uint8_uint8[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != uint8_uint8[i].fExpected )
          {
            // printf("Error in case uint8_uint8 throw: %02X, %02X, expected = %s\n",
            // uint8_uint8[i].x, uint8_uint8[i].y, uint8_uint8[i].fExpected ? "true" : "false");
            cerr << "Error in case uint8_uint8 throw: ";
            cerr << hex << setw(2) << setfill('0') << (unsigned int)uint8_uint8[i].x << ", ";
            cerr << hex << setw(2) << setfill('0') << (unsigned int)uint8_uint8[i].y << ", ";
            cerr << "expected = " << uint8_uint8[i].fExpected << endl;
          }
      }
  }

#if !defined __GNUC__
#pragma warning( disable: 4309 )
#endif

  static const MultTest< __int8, __int8 > int8_int8[] = 
    {
      { 0,      0, true },
      { 1,      0, true },
      { 2,      0, true },
      { 4,      0, true },
      { 0x10,   0ULL, true },
      { 0x20,   0ULL, true },
      { 0x7f,   0ULL, true },
      { 0x80,   0ULL, true },
      { 0xc0,   0ULL, true },
      { 0xe0,   0ULL, true },
      { 0xfe,   0ULL, true },
      { 0xff,   0ULL, true },

      { 0,      1, true },
      { 1,      1, true },
      { 2,      1, true },
      { 4,      1, true },
      { 0x10,   1ULL, true },
      { 0x20,   1ULL, true },
      { 0x7f,   1ULL, true },
      { 0x80,   1ULL, true },
      { 0xc0,   1ULL, true },
      { 0xe0,   1ULL, true },
      { 0xfe,   1ULL, true },
      { 0xff,   1ULL, true },

      { 0,      2, true },
      { 1,      2, true },
      { 2,      2, true },
      { 4,      2, true },
      { 0x10,   2ULL, true },
      { 0x20,   2ULL, true },
      { 0x3f,   2ULL, true },
      { 0x40,   2ULL, false },
      { 0x7f,   2ULL, false },
      { 0x80,   2ULL, false },
      { 0xc0,   2ULL, true },
      { 0xe0,   2ULL, true },
      { 0xfe,   2ULL, true },
      { 0xff,   2ULL, true },

      { 0,      4, true },
      { 1,      4, true },
      { 2,      4, true },
      { 4,      4, true },
      { 0x10,   4ULL, true },
      { 0x1f,   4ULL, true },
      { 0x20,   4ULL, false },
      { 0x7f,   4ULL, false },
      { 0x80,   4ULL, false },
      { 0xc0,   4ULL, false },
      { 0xdf,   4ULL, false },
      { 0xe0,   4ULL, true },
      { 0xfe,   4ULL, true },
      { 0xff,   4ULL, true },

      { 0,      0x10ULL, true },
      { 1,      0x10ULL, true },
      { 2,      0x10ULL, true },
      { 4,      0x10ULL, true },
      { 7,      0x10ULL, true },
      { 8,      0x10ULL, false },
      { 0x10,   0x10ULL, false },
      { 0x20,   0x10ULL, false },
      { 0x7f,   0x10ULL, false },
      { 0x80,   0x10ULL, false },
      { 0xc0,   0x10ULL, false },
      { 0xe0,   0x10ULL, false },
      { 0xf7,   0x10ULL, false },
      { 0xf8,   0x10ULL, true },
      { 0xfe,   0x10ULL, true },
      { 0xff,   0x10ULL, true },

      { 0,      0x20ULL, true },
      { 1,      0x20ULL, true },
      { 2,      0x20ULL, true },
      { 3,      0x20ULL, true },
      { 4,      0x20ULL, false },
      { 0x10,   0x20ULL, false },
      { 0x20,   0x20ULL, false },
      { 0x7f,   0x20ULL, false },
      { 0x80,   0x20ULL, false },
      { 0xc0,   0x20ULL, false },
      { 0xe0,   0x20ULL, false },
      { 0xfb,   0x20ULL, false },
      { 0xfc,   0x20ULL, true },
      { 0xfe,   0x20ULL, true },
      { 0xff,   0x20ULL, true },

      { 0,      0x40ULL, true },
      { 1,      0x40ULL, true },
      { 2,      0x40ULL, false },
      { 3,      0x40ULL, false },
      { 4,      0x40ULL, false },
      { 0x10,   0x40ULL, false },
      { 0x20,   0x40ULL, false },
      { 0x7f,   0x40ULL, false },
      { 0x80,   0x40ULL, false },
      { 0xc0,   0x40ULL, false },
      { 0xe0,   0x40ULL, false },
      { 0xfd,   0x40ULL, false },
      { 0xfe,   0x40ULL, true },
      { 0xff,   0x40ULL, true },

      { 0,      0x7fULL, true },
      { 1,      0x7fULL, true },
      { 2,      0x7fULL, false },
      { 4,      0x7fULL, false },
      { 0x10,   0x7fULL, false },
      { 0x20,   0x7fULL, false },
      { 0x7f,   0x7fULL, false },
      { 0x80,   0x7fULL, false },
      { 0xc0,   0x7fULL, false },
      { 0xe0,   0x7fULL, false },
      { 0xfe,   0x7fULL, false },
      { 0xff,   0x7fULL, true },

      { 0,      0x80ULL, true },
      { 1,      0x80ULL, true },
      { 2,      0x80ULL, false },
      { 3,      0x80ULL, false },
      { 4,      0x80ULL, false },
      { 0x10,   0x80ULL, false },
      { 0x20,   0x80ULL, false },
      { 0x7f,   0x80ULL, false },
      { 0x80,   0x80ULL, false },
      { 0xc0,   0x80ULL, false },
      { 0xe0,   0x80ULL, false },
      { 0xfe,   0x80ULL, false },
      { 0xff,   0x80ULL, false },

      { 0,      0xfeULL, true },
      { 1,      0xfeULL, true },
      { 2,      0xfeULL, true },
      { 4,      0xfeULL, true },
      { 0x10,   0xfeULL, true },
      { 0x20,   0xfeULL, true },
      { 0x40,   0xfeULL, true },
      { 0x41,   0xfeULL, false },
      { 0x7f,   0xfeULL, false },
      { 0x80,   0xfeULL, false },
      { 0xc0,   0xfeULL, false },
      { 0xdf,   0xfeULL, true },
      { 0xe0,   0xfeULL, true },
      { 0xff,   0xfeULL, true },

      { 0,      0xffULL, true },
      { 1,      0xffULL, true },
      { 2,      0xffULL, true },
      { 4,      0xffULL, true },
      { 0x10,   0xffULL, true },
      { 0x20,   0xffULL, true },
      { 0x7f,   0xffULL, true },
      { 0x80,   0xffULL, false },
      { 0xc0,   0xffULL, true },
      { 0xe0,   0xffULL, true },
      { 0xff,   0xffULL, true },
    };

#if !defined __GNUC__
#pragma warning( default: 4309 )
#endif

  void MultVerifyInt8Int8()
  {
    size_t i;

    for( i = 0; i < COUNTOF(int8_int8); ++i )
      {
        __int8 ret;
        if( SafeMultiply(int8_int8[i].x, int8_int8[i].y, ret) != int8_int8[i].fExpected )
          {
            //assert(false);
            // printf("Error in case int8_int8: %02X, %02X, expected = %s\n",
            // int8_int8[i].x, int8_int8[i].y, int8_int8[i].fExpected ? "true" : "false");
            cerr << "Error in case int8_int8: ";
            cerr << hex << setw(2) << setfill('0') << (unsigned int)int8_int8[i].x << ", ";
            cerr << hex << setw(2) << setfill('0') << (unsigned int)int8_int8[i].y << ", ";
            cerr << "expected = " << int8_int8[i].fExpected << endl;
          }

        // Now test throwing version
        bool fSuccess = true;
        try
          {
            SafeInt<__int8> si(int8_int8[i].x);
            si *= int8_int8[i].y;
          }
        catch(...)
          {
            fSuccess = false;
          }

        if( fSuccess != int8_int8[i].fExpected )
          {
            // printf("Error in case int8_int8 throw: %02X, %02X, expected = %s\n",
            // int8_int8[i].x, int8_int8[i].y, int8_int8[i].fExpected ? "true" : "false");
            cerr << "Error in case int8_int8 throw: ";
            cerr << hex << setw(2) << setfill('0') << (unsigned int)int8_int8[i].x << ", ";
            cerr << hex << setw(2) << setfill('0') << (unsigned int)int8_int8[i].y << ", ";
            cerr << "expected = " << int8_int8[i].fExpected << endl;
          }
      }
  }

  void MultVerify()
  {
    cout << "Verifying Multiplication:" << endl;

    MultVerifyUint64Uint64();
    MultVerifyUint64Uint();
    MultVerifyUint64Int64();
    MultVerifyUint64Int();

    MultVerifyUintUint64();
    MultVerifyUintInt64();

    MultVerifyInt64Int64();
    MultVerifyInt64Uint64();
    MultVerifyInt64Int();
    MultVerifyInt64Uint();

    MultVerifyIntInt64();
    MultVerifyIntUint64();

    MultVerifyInt8Int8();
    MultVerifyUint8Uint8();
  }

}
