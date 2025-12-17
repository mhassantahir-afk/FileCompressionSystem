//
// Created by Mrjoe on 12/14/2025.
//
#include <iostream>
#include "algorithms/LZ77.h"

using namespace std;

int main() {
    cout << "=== LZ77 Compression Test ===" << endl << endl;

    LZ77 lz;

    // Test compression
    cout << "Compressing file..." << endl;
    lz.compress("../resources/TestFiles/uncompressed/uncompressed_1.txt", "../resources/TestFiles/compressed/CompressedFileOutofLZ77.lz77");
    cout << "File compressed successfully!" << endl << endl;

    // Test decompression
    cout << "Decompressing file..." << endl;
    lz.decompress("../resources/TestFiles/compressed/CompressedFileOutofLZ77.lz77", "../resources/TestFiles/uncompressed/UncompressedFileOutofLZ77.txt");
    cout << "File decompressed successfully!" << endl << endl;

    cout << "Done! Check restored.txt to verify it matches the original." << endl;

    return 0;
}