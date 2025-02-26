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

    struct Node {
        unsigned char byte;
        unsigned char ch;
        int freq;
        Node *left;
        Node *right;
        Node(unsigned char byte, int freq) : byte(byte), freq(freq), left(nullptr), right(nullptr) {}
    };
    
    struct NodePtrComp {
        bool operator()(const Node* lhs, const Node* rhs) const {
            return lhs->freq > rhs->freq;
        }
    };
    void generateCodes(Node* root, const std::string &prefix, std::vector<std::string> &codes);

private:
    // You can add private helper functions or member variables here

    
};

#endif // HEADER_H
