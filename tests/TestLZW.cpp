//
// Created by Mrjoe on 12/15/2025.
//
#include <iostream>
#include "algorithms/LZW.h"
#include "datastructures/Trie.h"
#include "datastructures/HashTable.h"

using namespace std;

int main() {
    cout << "=== LZW Compression Test ===" << endl << endl;

    LZW lzw;

    // Compress
    cout << "Compressing file..." << endl;
    Trie compressionTrie;
    lzw.compress("../resources/TestFiles/uncompressed/uncompressed_1.txt",
                 "../resources/TestFiles/compressed/CompressedFileOutofLZW.lzw",
                 compressionTrie);
    cout << "Compression complete!" << endl << endl;

    // Decompress
    cout << "Decompressing file..." << endl;
    HashTable decompressionTable;
    lzw.decompress("../resources/TestFiles/compressed/CompressedFileOutofLZW.lzw",
                   "../resources/TestFiles/uncompressed/UncompressedFileOutofLZW.txt",
                   decompressionTable);
    cout << "Decompression complete!" << endl << endl;

    cout << "Done! Check restored.txt to verify it matches the original." << endl;

    return 0;
}