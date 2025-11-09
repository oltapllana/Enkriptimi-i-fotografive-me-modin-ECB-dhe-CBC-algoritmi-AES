// ====================================================================
// File: aes_cbc.h / aes_cbc.cpp — AES CBC module template
// ====================================================================
// Purpose:
// - Encrypt data using AES in CBC mode
// - CBC uses an initialization vector (IV) for chaining
// - Inputs: plaintext bytes, key bytes (16, 24, 32 bytes), IV (16 bytes)
// - Output: encrypted bytes
// ====================================================================

#include <vector>
#include <string>

// AES CBC encryption function declaration
// Steps to implement in aes_cbc.cpp:
// 1. Validate key size (16, 24, 32 bytes) and IV size (16 bytes)
// 2. Create OpenSSL EVP_CIPHER_CTX context
// 3. Select AES-128/192/256 CBC based on key length
// 4. Initialize encryption context with key and IV
// 5. Enable PKCS#7 padding
// 6. Allocate output buffer (plaintext + AES block size)
// 7. Encrypt plaintext with EVP_EncryptUpdate
// 8. Finalize encryption with EVP_EncryptFinal_ex
// 9. Resize buffer to final ciphertext size
// 10. Free context and return encrypted bytes
// Notes:
// - main.cpp is responsible for providing the IV for CBC mode
// - IV can be generated randomly or provided from file/hex
std::vector<unsigned char> aes_cbc_encrypt(const std::vector<unsigned char>& plaintext,
                                           const std::vector<unsigned char>& key,
                                           const std::vector<unsigned char>& iv);
