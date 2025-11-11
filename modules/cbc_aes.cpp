// ============================================================
// File: cbc_aes.cpp
// Description: Implements AES encryption/decryption in CBC mode.
// CBC mode chains blocks by XORing with the previous ciphertext.
// ============================================================

#include "cbc_aes.h"

// TODO:
// 1. Implement encryptCBC():
//    - Split plaintext into 16-byte blocks.
//    - XOR each block with the previous ciphertext (or IV for first block).
//    - Encrypt the block using AES core functions.
// 2. Implement decryptCBC():
//    - Decrypt ciphertext block.
//    - XOR decrypted block with previous ciphertext (or IV).
// 3. Handle PKCS#7 padding/unpadding.
