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

// TODO:
// 1. Implement encryptECB():
//    - Split plaintext into 16-byte blocks.
//    - Apply AES encryption on each block independently.
// 2. Implement decryptECB():
//    - Decrypt each block independently.
// 3. Optionally: Pad plaintext to multiple of 16 bytes (PKCS#7 padding).