// ===== Imports =====
#include <iostream>
// iostream, vector, string
// encryptor.hpp, file_utils.hpp

// ===== Helper Functions =====
// printUsage()      -> show CLI usage

void printUsage() {
    std::cout << "Usage: aes_tool <encrypt|decrypt> <ecb|cbc> <key_file> <input_file> <output_file>\n";
}
// parseMode()       -> convert "ecb"/"cbc" to AESMode enum
//AESMode parseMode(const std::string& modeStr) {
   // if (modeStr == "ecb") return AESMode::ECB;
  //  if (modeStr == "cbc") return AESMode::CBC;
   // throw std::invalid_argument("Invalid mode: " + modeStr);
//}

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
