#include <vector>
#include <string>
#include "ecb_aes.h"
#include <stdexcept>

// PKCS7 padding ----------------------------------------------------
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