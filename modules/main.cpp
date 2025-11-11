// ============================================================================
// File: main.cpp
// ============================================================================
// Purpose:
//  - Ngarkon një fotografi binare (BMP, PNG, etj.)
//  - Enkripton atë duke përdorur AES në modin ECB ose CBC.
//  - Ruajnë rezultatin si file të ri (p.sh. encrypted_ecb.bmp).
// ============================================================================


// ============================================================================
// File: main.cpp
// ============================================================================
// Purpose:
//  - Ngarkon një fotografi binare (BMP, PNG, etj.)
//  - Enkripton ose dekripton atë duke përdorur AES në modin ECB ose CBC.
//  - Ruajnë rezultatin si file të ri (p.sh. encrypted_ecb.bmp).
// ============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "ecb_aes.h"
#include "cbc_aes.h"

// ============================================================================
// ENUMS dhe strukturat ndihmëse
// ============================================================================
enum class AESMode { ECB, CBC };

// ============================================================================
// Helper Functions
// ============================================================================

// Printon mënyrën e përdorimit në CLI
void printUsage() {
    std::cout << "Usage:\n"
              << "  aes_tool <encrypt|decrypt> <ecb|cbc> <key_file> <input_file> <output_file>\n"
              << "Example:\n"
              << "  aes_tool encrypt cbc key.bin input.bmp encrypted_cbc.bmp\n";
}

// Konverton tekstin “ecb” / “cbc” në një vlerë të enumit AESMode
AESMode parseMode(const std::string& modeStr) {
    if (modeStr == "ecb") return AESMode::ECB;
    if (modeStr == "cbc") return AESMode::CBC;
    throw std::invalid_argument("Invalid mode: must be 'ecb' or 'cbc'");
}

// Lexon një file binar në një vector<uint8_t>
std::vector<uint8_t> readBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open file: " + filename);
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), {});
}

// Ruajnë vector<uint8_t> në një file binar
void writeBinaryFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to write file: " + filename);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

int main(int argc, char* argv[]) {
    // 1. Validate CLI arguments
    if (argc != 6) {
        printUsage();
        return 1;
    }

    // 2. Parse action, mode, key file, input file, output file
    // 3. Try/Catch block:
    //      a. Convert mode string to AESMode
    //      b. Load key from file
    //      c. Initialize Encryptor with key and mode
    //      d. Read input file
    //      e. Encrypt or decrypt based on action
    //      f. Write output file
    //      g. Print success messages
    // 4. Handle exceptions and errors
    // 5. Return 0 on success
}
