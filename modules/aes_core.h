#pragma once
// ============================================================
// File: aes_core.h
// Description: AES-128 core functions (encrypt/decrypt a 16-byte block)
// ============================================================
#include <vector>
#include <cstdint>

class AESCore {
public:
    AESCore(const std::vector<uint8_t>& key);  // key = 16 bytes (AES-128)

    std::vector<uint8_t> encryptBlock(const std::vector<uint8_t>& block);
    std::vector<uint8_t> decryptBlock(const std::vector<uint8_t>& block);

private:
    void keyExpansion();
    void addRoundKey(std::vector<uint8_t>& state, int round);
    void subBytes(std::vector<uint8_t>& state);
    void invSubBytes(std::vector<uint8_t>& state);
    void shiftRows(std::vector<uint8_t>& state);
    void invShiftRows(std::vector<uint8_t>& state);
    void mixColumns(std::vector<uint8_t>& state);
    void invMixColumns(std::vector<uint8_t>& state);

    std::vector<uint8_t> roundKeys; // expanded key
};
