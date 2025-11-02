// Simple XOR key for demonstration (replace with proper key expansion)
AESCore::AESCore(const std::vector<uint8_t>& key) {
    if (key.size() != 16) throw std::invalid_argument("Only AES-128 supported (16 bytes key)");
       roundKeys.resize(176);
    for (int i = 0; i < 16; i++)
        roundKeys[i] = key[i];

    keyExpansion();
}
// ---------------------------------------------------------
// Helper: galois multiply
// ---------------------------------------------------------

static uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t r = 0;
    while (b) {
        if (b & 1) r ^= a;
        bool hi = a & 0x80;
        a <<= 1;
        if (hi) a ^= 0x1b;
        b >>= 1;
    }
    return r;
}

void AESCore::keyExpansion() { 
    int bytesUsed = 16;
    int rconIter = 1;
    uint8_t temp[4];

    while (bytesUsed < 176) {
        for (int i = 0; i < 4; i++)
            temp[i] = roundKeys[bytesUsed - 4 + i];

        if (bytesUsed % 16 == 0) {
            uint8_t t = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = t;

            temp[0] = sbox[temp[0]];
            temp[1] = sbox[temp[1]];
            temp[2] = sbox[temp[2]];
            temp[3] = sbox[temp[3]];

            temp[0] ^= Rcon[rconIter++];
        }

        for (int i = 0; i < 4; i++) {
            roundKeys[bytesUsed] =
                roundKeys[bytesUsed - 16] ^ temp[i];
            bytesUsed++;
        }
    }
 }



 
#include <stdexcept>

static std::vector<uint8_t> padPKCS7(const std::vector<uint8_t>& data) {
    size_t padding = 16 - (data.size() % 16);
    std::vector<uint8_t> out = data;
    out.insert(out.end(), padding, static_cast<uint8_t>(padding));
    return out;
}
