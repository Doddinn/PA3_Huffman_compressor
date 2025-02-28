Group: Karl vidar, Þórður, Anton Elvar.

# header.h #
- Purpose
    Declaration of the Compressor class with methods for compression and decompression.
    Definition of the Node struct used for building the Huffman tree.
    Declaration of helper functions such as generateCodes for recursively generating Huffman codes.

# compressor.cpp #
- Purpose
    Frequency Table Creation:
        Reads the input file in binary mode and counts the frequency of each byte (0–255).
    Huffman Tree Construction:
        Uses a priority queue to build the Huffman tree from the frequency table. Handles edge cases (a file with only one unique byte).
    Code Generation:
        Implements the generateCodes function to traverse the Huffman tree and generate a binary code (as a string) for each character.
    File Header and Data Writing:
        Writes the frequency table as a header to the output file. Then re-reads the input file, encodes the data using the generated Huffman codes, packs bits into bytes and writes the compressed data.
    Memory Cleanup:
        Provides helper functions (like freeTree) to deallocate the Huffman tree and prevent memory leaks

# main.cpp #
- Purpose
    Serves as the entry point for the application.
    Command-Line Parsing:
        Processes command-line arguments to determine whether to compress (-c) or decompress (-u) a file, along with the input and output file names.
    Object Management:
        Creates an instance of the Compressor class and invokes the appropriate function (compress or decompress).
    Usage Instructions:
        Displays proper usage if the user does not provide the correct number or format of command-line arguments.
