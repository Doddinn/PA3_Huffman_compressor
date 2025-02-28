#include "header.h"
#include <iostream>
#include <queue>
#include <cstdint>



struct Node {
    unsigned char byte;
    int freq;
    Node *left;
    Node *right;
    Node(unsigned char byte, int freq) : byte(byte), freq(freq), left(nullptr), right(nullptr) {}
};


// Constructor
Compressor::Compressor() {
    // Initialize any resources if needed
    std::cout << "Compressor object created" << std::endl;
}

// Destructor
Compressor::~Compressor() {
    // Clean up any resources if needed
    if (huffmanTreeRoot){
        freeTree(huffmanTreeRoot);
        huffmanTreeRoot = nullptr;
    }
    std::cout << "Compressor object destroyed" << std::endl;
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


    // write header.. in this case  what is written is the freq table 256 integers
    // the decompressor can rebuild the tree using the tree fro mthe table
    for (int i = 0; i < 256; i++){
        out.write(reinterpret_cast<const char*>(&freq[i]), sizeof(int));
    }

    // read input again, encode using the code table and pack bits into bytes
    std::string bitString;
    while (in.get(byte)) {
        unsigned char ch = static_cast<unsigned char>(byte);
        bitString += codeTable[ch];
        // write out bytes as soon as we have at least 8 bits
        while (bitString.size() >= 8) {
            std::string byteString = bitString.substr(0, 8);
            bitString.erase(0, 8);
            //convert 8 bit string to a single byte
            uint8_t outByte = 0;
            for (int i = 0; i < 8; i++) {
                outByte = (outByte << 1) | (byteString[i] - '0');
            }
            out.write(reinterpret_cast<const char*>(&outByte), sizeof(uint8_t));
        }
    }

    // if any bits remain, pad them to form a full byte
    int padding = 0;
    if (!bitString.empty()) {
        padding = 8 - bitString.size();
        // pad with zeros
        bitString.append(padding, '0');
        uint8_t outByte = 0;
        for (int i = 0; i < 8; i++) {
            outByte = (outByte << 1) | (bitString[i] - '0');
        }
        out.write(reinterpret_cast<const char*>(&outByte), sizeof(uint8_t));
    }

    // write the padding to the output file so that the decompressor can remove it
    out.write(reinterpret_cast<const char*>(&padding), sizeof(int));

    // clean up
    freeTree(huffmanTree);
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


    in.close();
    out.close();
    return true;
}
