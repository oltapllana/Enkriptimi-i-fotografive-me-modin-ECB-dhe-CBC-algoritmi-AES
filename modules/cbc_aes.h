// ============================================================================
// File: cbc_aes.h
// ============================================================================
// Purpose:
//  - Implementon AES në modin CBC (Cipher Block Chaining).
//  - Çdo bllok XOR-ohet me bllokun paraprak të ciphertext-it.
//  - Përdor një IV (Initialization Vector) për bllokun e parë.
// ============================================================================
#pragma once
#include "aes_core.h"

class AESCipherCBC {
public:
    AESCipherCBC(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv);
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data);

private:
    AESCore aes;
    std::vector<uint8_t> iv;
};