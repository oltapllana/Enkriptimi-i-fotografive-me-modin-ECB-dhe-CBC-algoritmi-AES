// ============================================================================
// File: cbc_aes.h
// ============================================================================
// Purpose:
//  - Implementon AES në modin CBC (Cipher Block Chaining).
//  - Çdo bllok XOR-ohet me bllokun paraprak të ciphertext-it.
//  - Përdor një IV (Initialization Vector) për bllokun e parë.
// ============================================================================
// ============================================================================
#pragma once
#include "aes_core.h"
#include <vector>

std::vector<uint8_t> encryptCBC(const std::vector<uint8_t>& data,
                                const std::vector<uint8_t>& key,
                                const std::vector<uint8_t>& iv);

std::vector<uint8_t> decryptCBC(const std::vector<uint8_t>& data,
                                const std::vector<uint8_t>& key,
                                const std::vector<uint8_t>& iv, bool removePadding);
