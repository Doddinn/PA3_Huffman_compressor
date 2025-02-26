#include "header.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstring>

struct Node {
    unsigned char ch;  // only valid for leaf nodes
    unsigned char byte;
    int freq;
    Node *left;
    Node *right;
    Node(unsigned char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

void Compressor::generateCodes(Node* root, const std::string &prefix, std::vector<std::string> &codes){
    if (!root) return;

    if (!root->left && !root->right){
        codes[static_cast<unsigned char>(root->ch)] = prefix;
        return;
    }

    generateCodes(root->left, prefix + "0", codes);
    generateCodes(root->right, prefix + "1", codes);
}

// Constructor
Compressor::Compressor() {
    // Initialize any resources if needed
}

// Destructor
Compressor::~Compressor() {
    // Clean up any resources if needed
}


bool Compressor::compress(const std::string &inputFile, const std::string &outputFile) {
    // open input file in binary mode
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open input file: " << inputFile << "\n";
        return false;
    }
    // open output file in binary mode
    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file: " << outputFile << "\n";
        return false;
    }

    // TODO: Implement your compression logic here.
    // For example, you might read the entire file, build a frequency table,
    // construct a Huffman tree, generate a code table, and then write the header and compressed data.
    
    // frequency table 256 posible byte value
    std::vector<int> freq(256, 0);
    char byte;
    while (in.get(byte)){
        freq[static_cast<unsigned char>(byte)]++;
    }

    // resetting file pointer to continue further readings
    in.clear();
    in.seekg(0, std::ios::beg);

    // building huffman tree using min heap
    std::priority_queue<Node*, std::vector<Node*>, NodePtrComp> pq; 
    for (int i = 0; i < 256; i++){
        if (freq[i] > 0){
            pq.push(new Node(i, freq[i]));
        }
    }

    // if a file is empty
    if (pq.empty()){
        in.close();
        out.close();
        return false;
    }

    // in case the files contains only one unique byte create a dummy node
    if (pq.size() == 1){
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* parent = new Node(0, left->freq + right->freq);
        pq.push(parent);
    }
    Node* huffmanTree = pq.top();

    // now generate the huffman code table
    std::vector<std::string> codeTable(256);
    generateCodes(huffmanTree, "", codeTable);


    in.close();
    out.close();
    return true;
}

bool Compressor::decompress(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open input file: " << inputFile << "\n";
        return false;
    }

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file: " << outputFile << "\n";
        return false;
    }

    // TODO: Implement your decompression logic here.
    // Typically, you'll read the header (e.g., the code table) first,
    // rebuild the Huffman tree, and then decode the rest of the file.

    in.close();
    out.close();
    return true;
}
