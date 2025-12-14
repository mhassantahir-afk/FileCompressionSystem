//
// Created by Mrjoe on 12/13/2025.
//
#include "algorithms/huffman.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Testing Huffman Compression..." << endl;

    // Compress your file
    compressFile("../resources/TestFiles/uncompressed/uncompressed_1.txt", "../resources/TestFiles/compressed/CompressedFileOutofTestHuffman_1.huff");

    // Decompress it back
    decompressFile("../resources/TestFiles/compressed/CompressedFileOutofTestHuffman_1.huff", "../resources/TestFiles/uncompressed/UncompressedFileOutofTestHuffman_1.txt");

    cout << "Done! Check the restored.txt file." << endl;

    return 0;
}