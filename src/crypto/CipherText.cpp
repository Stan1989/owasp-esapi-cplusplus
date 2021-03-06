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

#include "EsapiCommon.h"
#include "crypto/CipherText.h"

#include "safeint/SafeInt3.hpp"

#include <sstream>
#include <algorithm>
#include <stdexcept>

namespace esapi
{
  CipherText::CipherText()
    : m_text()
  {
  }

  CipherText::~CipherText()
  {
  }

  bool CipherText::empty() const
  {
    return m_text.empty();
  }

  String CipherText::getCipherMode() const
  {
    return "CBC";
  }
}

