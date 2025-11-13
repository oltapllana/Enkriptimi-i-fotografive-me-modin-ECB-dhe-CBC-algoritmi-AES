#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include "ecb_aes.h"
#include "cbc_aes.h"

enum class AESMode { ECB, CBC };

void printUsage() {
    std::cout << "Usage:\n"
              << "  aes_tool <encrypt|decrypt> <ecb|cbc> <key_file> <input_file> <output_file>\n";
}

AESMode parseMode(const std::string& modeStr) {
    if (modeStr == "ecb") return AESMode::ECB;
    if (modeStr == "cbc") return AESMode::CBC;
    throw std::invalid_argument("Invalid mode: must be 'ecb' or 'cbc'");
}