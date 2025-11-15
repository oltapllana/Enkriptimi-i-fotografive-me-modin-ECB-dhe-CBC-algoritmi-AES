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
#include <random>
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

std::vector<uint8_t> readBinaryFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open file: " + filename);
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), {});
}

void writeBinaryFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to write file: " + filename);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

std::vector<uint8_t> generateRandomBytes(size_t size = 16) {
    std::vector<uint8_t> bytes(size);
    std::random_device rd;

    for (size_t i = 0; i < size; ++i) {
        bytes[i] = rd() % 256;
    }

    return bytes;
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        printUsage();
        return 1;
    }

    std::string action = argv[1];
    std::string modeStr = argv[2];
    std::string keyFile = argv[3];
    std::string inputFile = argv[4];
    std::string outputFile = argv[5];

    try {
        AESMode mode = parseMode(modeStr);
        auto key = readBinaryFile(keyFile);
        if (key.size() != 16)
            throw std::runtime_error("Key must be 16 bytes for AES-128");

        auto inputData = readBinaryFile(inputFile);
        std::vector<uint8_t> outputData;

        if (mode == AESMode::ECB) {
            // ECB mode does not use IV
            if (action == "encrypt") outputData = encryptECB(inputData, key);
            else if (action == "decrypt") outputData = decryptECB(inputData, key, true);
            else throw std::invalid_argument("Action must be 'encrypt' or 'decrypt'");
        }
        else if (mode == AESMode::CBC) {
            if (action == "encrypt") {
                // Generate random IV for this file
                auto iv = generateRandomBytes();
                // Save IV with same name as ciphertext but _iv.bin
                std::string ivFile = outputFile.substr(0, outputFile.find_last_of('.')) + "_iv.bin";
                writeBinaryFile(ivFile, iv);

                outputData = encryptCBC(inputData, key, iv);
            }
            else if (action == "decrypt") {
                // Read IV from corresponding file
                std::string ivFile = inputFile.substr(0, inputFile.find_last_of('.')) + "_iv.bin";
                auto iv = readBinaryFile(ivFile);
                if (iv.size() != 16)
                    throw std::runtime_error("IV must be 16 bytes for CBC decryption");

                outputData = decryptCBC(inputData, key, iv, true);
            }
            else throw std::invalid_argument("Action must be 'encrypt' or 'decrypt'");
        }

        writeBinaryFile(outputFile, outputData);
        std::cout << "[SUCCESS] " << action << "ed file saved to " << outputFile << "\n";

    } catch (const std::exception& ex) {
        std::cerr << "[ERROR] " << ex.what() << "\n";
        return 1;
    }

    return 0;
}