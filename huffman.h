#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>
#include <cctype>


struct Node{
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character, int frequency);
};

struct Compare{
    bool operator()(Node* a, Node* b);
};

void buildCodeTable(Node* root, const std::string& str, std::unordered_map<char, std::string>& codeTable);

void freeTree(Node* root);

#endif