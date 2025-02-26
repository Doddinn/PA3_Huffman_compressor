#include "huffman.h"



// Node constructor implementation.
Node::Node(char character, int frequency) 
    : ch(character), freq(frequency), left(nullptr), right(nullptr) {}

// compare functor implementation.
bool Compare::operator()(Node* a, Node* b) {
    return a->freq > b->freq;
}

// recursive function to build the Huffman code table.
void buildCodeTable(Node* root, const std::string& str, std::unordered_map<char, std::string>& codeTable) {
    if (!root)
        return;
    // if this is a leaf node, assign the code.
    if (!root->left && !root->right) {
        codeTable[root->ch] = str;
    }
    buildCodeTable(root->left, str + "0", codeTable);
    buildCodeTable(root->right, str + "1", codeTable);
}

// recursively free the memory allocated for the Huffman tree.
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
