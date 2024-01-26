/*
    Copyright 2023 Patricia Antlitz
*/
#include <sstream>
#include <fstream>
#include "RandWriter.hpp"

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cerr << "Arguments: ./TextWriter <k> <L> being" <<
            " k the order k and L the length" << std::endl;
        return 1;
    }

    // Parse command-line arguments
    int k, L;
    std::istringstream(argv[1]) >> k;
    std::istringstream(argv[2]) >> L;

    if (k <= 0 || L <= 0) {
        std::cerr << "Error: k and L must be positive integers." << std::endl;
        return 1;
    }

    // Read input
    std::string inputText;
    char ch;

    while (std::cin.get(ch)) {
        inputText += ch;
    }

    try {
        RandWriter randWriter(inputText, k);
        std::string generatedText = randWriter.generate(inputText.substr(0, k), L);

        // Print
        std::cout << generatedText << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
