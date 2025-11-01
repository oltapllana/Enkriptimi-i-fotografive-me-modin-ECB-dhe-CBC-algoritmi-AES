// ============================================================================
// File: ecb_aes.h
// ============================================================================
// Purpose:
//  - Implementon AES në modin ECB (Electronic Codebook).
//  - Çdo bllok 16-bajtësh enkriptohet në mënyrë të pavarur.
//  - Jo i sigurt për fotografi, por i mirë për demonstrim.
//
// ============================================================================
#pragma once
#include "aes_core.h"

class AESCipherECB {
public:
    explicit AESCipherECB(const std::vector<uint8_t>& key);
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data);

private:
    AESCore aes;
};