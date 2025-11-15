
#pragma once
#include "aes_core.h"
#include <vector>

std::vector<uint8_t> encryptECB(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key);
std::vector<uint8_t> decryptECB(const std::vector<uint8_t>& data, const std::vector<uint8_t>& key, bool removePadding);
