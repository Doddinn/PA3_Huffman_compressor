#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <queue>
#include <fstream>

class Compressor {
public:
    Compressor();// Constructor
    ~Compressor();// Destructor

    // Compresses the input file into the output file
    // returns true on success, false on error
    bool compress(const std::string &inputFile, const std::string &outputFile);

    // Decompresses the input file into the output file
    // returns true on success, false on error
    bool decompress(const std::string &inputFile, const std::string &outputFile);

    struct Node {
        unsigned char byte;
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

private:
    Node* huffmanTreeRoot;
    std::vector<std::string> codeTable;

    // Recursively generate Huffman codes from the tree.
    void generateCodes(Node* root, const std::string &prefix, std::vector<std::string> &codes) {
        if (!root) return;
        // leaf node: record the code
        if (!root->left && !root->right) {
            codes[static_cast<int>(root->byte)] = prefix;
            return;
        }
        generateCodes(root->left, prefix + "0", codes);
        generateCodes(root->right, prefix + "1", codes);
    }

    // Free the Huffman tree.
    void freeTree(Node* root) {
        if (!root) return;
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }

    // build huffman tree given the frequency table, frequency table should have 256 elements
    Node* buildHuffmanTree(const std::vector<int>& frequencies);

    // build frequency table from the input file, returns a vector of 256 elements
    std::vector<int> buildFrequencyTable(const std::string &data);

    // encode the input data using the code table, returns the encoded data
    std::string encodeData(const std::string &data, const std::vector<std::string> &codes);

    // decode the encoded data using the code table, returns the decoded data
    std::string decodeData(const std::string &encodedata, Node* root);

    // write the code table to the output file
    bool writeCodeTable(const std::vector<std::string> &codes, std::ofstream &out);

    // read the code table from the input file
    bool readCodeTable(std::ifstream &in, std::vector<std::string> &codes);
};

#endif // HEADER_H

