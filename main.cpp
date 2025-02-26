#include "huffman.h"

int main(int argc, char* argv[]) {
    // Ensure correct number of command-line arguments.
    if (argc < 4) {
        std::cout << "Usage: ./encoder -e|-d input_file output_file" << std::endl;
        return 1;
    }
    
    std::string mode = argv[1];
    std::string inputFile = argv[2];
    std::string outputFile = argv[3];
    
    if (mode == "-e") {  // Encoding mode
        std::ifstream inFile(inputFile);
        if (!inFile) {
            std::cerr << "Error opening input file." << std::endl;
            return 1;
        }
        
        // Count frequency of each character (ignoring whitespace).
        std::unordered_map<char, int> freqMap;
        char c;
        while (inFile >> std::noskipws >> c) {
            if (std::isspace(c))
                continue;
            freqMap[c]++;
        }
        
        // Build a priority queue (min-heap) for the Huffman tree.
        std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
        for (const auto& pair : freqMap) {
            pq.push(new Node(pair.first, pair.second));
        }
        
        // Build the Huffman tree.
        while (pq.size() > 1) {
            Node* left = pq.top();
            pq.pop();
            Node* right = pq.top();
            pq.pop();
            Node* parent = new Node('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            pq.push(parent);
        }
        Node* root = pq.top();
        
        // Build the Huffman code table.
        std::unordered_map<char, std::string> codeTable;
        buildCodeTable(root, "", codeTable);
        
        // Prepare to write output.
        std::ofstream outFile(outputFile);
        if (!outFile) {
            std::cerr << "Error opening output file." << std::endl;
            freeTree(root);
            return 1;
        }
        
        // Write the code table to the output file.
        // Each line: [character] [code]
        for (const auto& pair : codeTable) {
            outFile << pair.first << " " << pair.second << "\n";
        }
        // Write a special marker to indicate the end of the code table.
        outFile << "\\\n";
        
        // Reset the input file to re-read for encoding.
        inFile.clear();
        inFile.seekg(0);
        
        // Encode each line from the input file.
        std::string line;
        while (std::getline(inFile, line)) {
            std::string encodedLine;
            for (char ch : line) {
                // Skip whitespace characters.
                if (std::isspace(ch))
                    continue;
                encodedLine += codeTable[ch];
            }
            outFile << encodedLine << "\n";
        }
        
        // Clean up.
        outFile.close();
        inFile.close();
        freeTree(root);
    } 
    else if (mode == "-d") {  // Decoding mode (skeleton)
        // Steps to implement decoding:
        // 1. Open the encoded file.
        // 2. Read the code table until a marker (e.g., "\\") is encountered.
        // 3. Rebuild the Huffman tree from the code table.
        // 4. Decode each encoded line by traversing the tree.
        std::cout << "Decoding not implemented yet. Please complete this section." << std::endl;
    } 
    else {
        std::cerr << "Invalid mode. Use -e for encode or -d for decode." << std::endl;
        return 1;
    }
    
    return 0;
}
