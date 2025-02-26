#ifndef HEADER_H
#define HEADER_H

#include <string>

class Compressor {
public:
    Compressor();               // Constructor
    ~Compressor();              // Destructor

    // Compresses the input file into the output file.
    // Returns true on success, false on error.
    bool compress(const std::string &inputFile, const std::string &outputFile);

    // Decompresses the input file into the output file.
    // Returns true on success, false on error.
    bool decompress(const std::string &inputFile, const std::string &outputFile);

private:
    // You can add private helper functions or member variables here
};

#endif // HEADER_H
