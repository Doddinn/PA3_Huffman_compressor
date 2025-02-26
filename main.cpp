#include <iostream>
#include <string>
#include "header.h"  // Assumes Compressor class is declared here

int main(int argc, char* argv[]) {
    // Check for proper number of arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " -c|-u <input_file> <output_file>\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    // Create a Compressor object (assumes proper constructor)
    Compressor compressor;

    // Choose action based on the mode argument
    if (mode == "-c") {
        // Compress the input file and output the compressed file
        if (!compressor.compress(inputFile, outputFile)) {
            std::cerr << "Compression failed!\n";
            return 1;
        }
        std::cout << "File compressed successfully.\n";
    } else if (mode == "-u") {
        // Decompress the input file and output the original file
        if (!compressor.decompress(inputFile, outputFile)) {
            std::cerr << "Decompression failed!\n";
            return 1;
        }
        std::cout << "File decompressed successfully.\n";
    } else {
        std::cerr << "Invalid mode: " << mode << ". Use -c for compress or -u for uncompress.\n";
        return 1;
    }

    return 0;
}
