//
// Created by Mrjoe on 12/14/2025.
//
#include <iostream>
#include "algorithms/RLE.h"

using namespace std;

int main() {
    cout << "=== RLE Compression Test ===" << endl << endl;

    // Analyze the file first
    cout << "Analyzing file for RLE suitability..." << endl;
    analyzeFileForRLE("../resources/TestFiles/uncompressed_5.txt");
    cout << endl;

    // Compress
    cout << "Compressing file..." << endl;
    rleCompressFile("../resources/TestFiles/uncompressed/uncompressed_5.txt",
                    "../resources/TestFiles/compressed/CompressedFileOutofRLE.rle");
    cout << endl;

    // Decompress
    cout << "Decompressing file..." << endl;
    rleDecompressFile("../resources/TestFiles/compressed/CompressedFileOutofRLE.rle",
                      "../resources/TestFiles/uncompressed/UncompressedFileOutofRLE.txt");
    cout << endl;

    cout << "Done! Check restored.txt to verify it matches the original." << endl;

    return 0;
}