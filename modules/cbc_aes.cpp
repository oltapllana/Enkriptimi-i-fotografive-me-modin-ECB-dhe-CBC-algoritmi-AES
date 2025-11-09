#include "cbc_aes.h"
#include <stdexcept>

// TODO:
// 1. Implement encryptCBC():
//    - Split plaintext into 16-byte blocks.
//    - XOR each block with the previous ciphertext (or IV for first block).
//    - Encrypt the block using AES core functions.
// 2. Implement decryptCBC():
//    - Decrypt ciphertext block.
//    - XOR decrypted block with previous ciphertext (or IV).

static std::vector<uint8_t> padPKCS7(const std::vector<uint8_t>& data) {
    size_t padding = 16 - (data.size() % 16);
    std::vector<uint8_t> out = data;
    out.insert(out.end(), padding, static_cast<uint8_t>(padding));
    return out;
}

static std::vector<uint8_t> unpadPKCS7(const std::vector<uint8_t>& data) {
    if (data.empty() || data.size() % 16 != 0)
        throw std::runtime_error("Invalid padded data length");

    uint8_t padVal = data.back();
    if (padVal == 0 || padVal > 16)
        throw std::runtime_error("Invalid PKCS7 padding value");

    bool padding_ok = true; 
    
    for (size_t i = 0; i < padVal; i++) {
        if (data[data.size() - 1 - i] != padVal) {
            padding_ok = false;
        }
    }
    
    if (!padding_ok) {
        throw std::runtime_error("Invalid PKCS7 padding bytes detected");
    }

    return std::vector<uint8_t>(data.begin(), data.end() - padVal);
}

std::vector<uint8_t> encryptCBC(const std::vector<uint8_t>& data,
                                const std::vector<uint8_t>& key,
                                const std::vector<uint8_t>& iv)
{
    AESCore aes(key);
    std::vector<uint8_t> input = padPKCS7(data);

    std::vector<uint8_t> output;
    std::vector<uint8_t> prevBlock = iv;

    for (size_t i = 0; i < input.size(); i += 16) {
        std::vector<uint8_t> block(input.begin() + i, input.begin() + i + 16);

        for (size_t j = 0; j < 16; j++)
            block[j] ^= prevBlock[j];

        auto encrypted = aes.encryptBlock(block);

        output.insert(output.end(), encrypted.begin(), encrypted.end());
        prevBlock = encrypted;
    }

    return output;
}