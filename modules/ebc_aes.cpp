// ====================================================================
// File: aes_ecb.h / aes_ecb.cpp — AES ECB module template
// ====================================================================
// Purpose:
// - Encrypt data using AES in ECB mode
// - ECB encrypts each block independently
// - Inputs: plaintext bytes and key bytes (16, 24, 32 bytes)
// - Output: encrypted bytes
// ====================================================================

#include <vector>
#include <string>

// AES ECB encryption function declaration
// Steps to implement in aes_ecb.cpp:
// 1. Validate key size (AES supports 128, 192, 256 bit keys)
// 2. Create OpenSSL EVP_CIPHER_CTX context
// 3. Select AES-128/192/256 ECB based on key length
// 4. Initialize encryption context
// 5. Enable PKCS#7 padding
// 6. Allocate output buffer (plaintext + AES block size)
// 7. Encrypt plaintext with EVP_EncryptUpdate
// 8. Finalize encryption with EVP_EncryptFinal_ex
// 9. Resize buffer to final ciphertext size
// 10. Free context and return encrypted bytes
std::vector<unsigned char> aes_ecb_encrypt(const std::vector<unsigned char>& plaintext,
                                           const std::vector<unsigned char>& key);