//
// Created by Mrjoe on 12/15/2025.
//
#include <iostream>
#include "algorithms/Deflate.h"

using namespace std;

int main() {
    cout << "=== Deflate Compression Test ===" << endl << endl;

    Deflate deflate;

    // Compress
    cout << "Compressing file with DEFLATE..." << endl;
    deflate.compress("../resources/TestFiles/uncompressed/uncompressed_1.txt",
                     "../resources/TestFiles/compressed/CompressedFileOutofDeflate.deflate");
    cout << endl;

    // Decompress
    cout << "Decompressing file..." << endl;
    deflate.decompress("../resources/TestFiles/compressed/CompressedFileOutofDeflate.deflate",
                       "../resources/TestFiles/uncompressed/UncompressedFileOutofDeflate.txt");
    cout << endl;

    cout << "Done! Check restored.txt to verify it matches the original." << endl;

    return 0;
}