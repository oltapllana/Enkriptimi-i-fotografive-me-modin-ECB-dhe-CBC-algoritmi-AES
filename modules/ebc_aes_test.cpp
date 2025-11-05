#include "ecb_aes.h"
#include <stdexcept>

static std::vector<uint8_t> padPKCS7(const std::vector<uint8_t>& data) {
    size_t padding = 16 - (data.size() % 16);
    std::vector<uint8_t> out = data;
    out.insert(out.end(), padding, static_cast<uint8_t>(padding));
    return out;
}