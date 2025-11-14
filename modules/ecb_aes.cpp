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

std::vector<uint8_t> encryptECB(const std::vector<uint8_t>& data,
                                const std::vector<uint8_t>& key) 
{
    AESCore aes(key);
    std::vector<uint8_t> input = padPKCS7(data);
    std::vector<uint8_t> output;

    for (size_t i = 0; i < input.size(); i += 16) {
        std::vector<uint8_t> block(input.begin() + i, input.begin() + i + 16);
        auto encrypted = aes.encryptBlock(block);
        output.insert(output.end(), encrypted.begin(), encrypted.end());
    }

    return output;
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