#include <iostream>
#include <string>
#include "header.h"

int main(int argc, char* argv[]) {
    // check for proper number of arguments
    if (argc != 4) { // if the number of arguments is not 4
        // print usage message and return error
        std::cerr << "Usage: " << argv[0] << " -c|-u <input_file> <output_file>\n";
        return 1;
    }
    
    // extract the arguments
    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    // create a Compressor object assumes proper constructor
    Compressor compressor;

    // choose action based on the mode argument
    if (mode == "-c") {
        // compress the input file and output the compressed file
        if (!compressor.compress(inputFile, outputFile)) { // if compression fails
            std::cerr << "Compression failed!\n";
            return 1;
        }
        std::cout << "File compressed successfully.\n";
    } else if (mode == "-u") {
        // decompress the input file and output the original file
        if (!compressor.decompress(inputFile, outputFile)) { // if decompression fails
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
