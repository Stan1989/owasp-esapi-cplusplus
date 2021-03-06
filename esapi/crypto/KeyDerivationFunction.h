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

#include "crypto/CryptoppCommon.h"
#include "crypto/SecretKey.h"

/**
 * This class implements a Key Derivation Function (KDF) and supporting methods.
 * A KDF is a function with which an input key (called the Key Derivation Key,
 * or KDK) and other input data are used to securely generate (i.e., derive)
 * keying material that can be employed by cryptographic algorithms.
 * 
 * Acknowledgments:
 * ESAPI's KDF is patterned after suggestions first made by cryptographer
 * Dr. David A. Wagner and later extended to follow KDF in counter mode
 * as specified by section 5.1 of NIST SP 800-108. Jeffrey Walton and the NSA
 * also made valuable suggestions regarding the modeling of the method,
 * {@link #computeDerivedKey(SecretKey, int, String)}.
 *
 * @author Kevin Wall, kevin.w.wall@gmail.com
 * @author Jeffrey Walton, noloader@gmail.com
 */

namespace esapi
{
  // Forward declaration due to circular dependencies
  class SecretKey;

  class ESAPI_EXPORT KeyDerivationFunction
  {
  public:
    /**
     * The method is ESAPI's Key Derivation Function (KDF) that computes a
     * derived key from the {@code keyDerivationKey} for either
     * encryption / decryption or for authentication.
     * 
     * CAUTION: If this algorithm for computing derived keys from the
     * key derivation key is ever changed, we risk breaking backward compatibility of being
     * able to decrypt data previously encrypted with earlier / different versions
     * of this method. Therefore, do not change this unless you are 100% certain that
     * what you are doing will NOT change either of the derived keys for
     * ANY "key derivation key" AT ALL!!!
     * 
     * NOTE: This method is generally not intended to be called separately.
     * It is used by ESAPI's reference crypto implementation class {@code JavaEncryptor}
     * and might be useful for someone implementing their own replacement class, but
     * generally it is not something that is useful to application client code.
     *
     * @param keyDerivationKey A key used as an input to a key derivation function
     * to derive other keys. This is the key that generally
     * is created using some key generation mechanism such as
     * {@link #generateSecretKey(String, int)}. The
     * "input" key from which the other keys are derived.
     * The derived key will have the same algorithm type * as this key. This KDK cannot be null.
     * @param keySizeThe cipher's key size (in bits) for the {@code keyDerivationKey}.
     * Must have a minimum size of 56 bits and be an integral multiple of 8-bits.
     * Note: The derived key will have the same size as this.
     * @param purpose The purpose for the derived key. For the ESAPI reference implementation,
     * {@code JavaEncryptor}, this must be either the string "encryption" or
     * "authenticity", where "encryption" is used for creating a derived key to use
     * for confidentiality, and "authenticity" is used for creating a derived key to
     * use with a MAC to ensure message authenticity. However, since parameter serves
     * the same purpose as the "Labe" in section 5.1 of NIST SP 800-108, it really can
     * be set to anything other than {@code null} or an empty string when called outside
     * of {@code JavaEncryptor}.
     * @returnThe derived {@code SecretKey} to be used according
     * to the specified purpose.
     * @throws NoSuchAlgorithmExceptionThe {@code keyDerivationKey} has an unsupported
     * encryption algorithm or no current JCE provider supports
     * "HmacSHA1".
     * @throws EncryptionExceptionIf "UTF-8" is not supported as an encoding, then
     * this is thrown with the original {@code UnsupportedEncodingException}
     * as the cause. (NOTE: This should never happen as "UTF-8" is supposed to
     * be a common encoding supported by all Java implementations. Support
     * for it is usually in rt.jar.)
     */
    static SecretKey computeDerivedKey(const SecretKey& keyDerivationKey, unsigned int keyBits, const NarrowString& purpose);

    /**
     * Check if specified algorithm name is a valid PRF that can be used.
     * @param prfAlgNameName of the PRF algorithm; e.g., "HmacSHA1", "HmacSHA384", etc.
     * @returnTrue if {@code prfAlgName} is supported, otherwise false.
     */
    //public static boolean isValidPRF(String prfAlgName);
    //public static PRF_ALGORITHMS convertNameToPRF(String prfAlgName);
    //public static PRF_ALGORITHMS convertIntToPRF(int selection);

    /**
     * Calculate the size of a key. The key size is given in bits, but we
     * can only allocate them by octets (i.e., bytes), so make sure we
     * round up to the next whole number of octets. For example, a key
     * size of 9 bits would require 2 octets to store it.
     * @param keyBits The key size, in bits.
     * @return The key size, in octets, large enough to accommodate
     * {@code keyBits} bits.
     * @throws <i>YEP!</i>, if you wrap the value.
     */
    static unsigned int calcKeySize(unsigned int keyBits);

  private:
    KeyDerivationFunction() { /** No instantiation */ };
  };

} // NAMESPACE esapi

