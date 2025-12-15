//
// Created by Mrjoe on 12/15/2025.
//
#include <iostream>
#include <string>
#include <filesystem>

// Algorithms
#include "algorithms/huffman.h"
#include "algorithms/LZW.h"
#include "algorithms/lz77.h"
#include "algorithms/RLE.h"
#include "algorithms/Deflate.h"
#include "algorithms/ArithmeticCoding.h"

// Data structures
#include "datastructures/Trie.h"
#include "datastructures/HashTable.h"

namespace fs = std::filesystem;
using namespace std;

// ------------------------------------------------------------
// Utility
// ------------------------------------------------------------
string removeExtension(const string& path) {
    return fs::path(path).replace_extension("").string();
}

// ------------------------------------------------------------
// Compression Menu
// ------------------------------------------------------------
void compressFileCLI(const string& inputPath) {
    cout << "\nChoose compression algorithm:\n";
    cout << "1. Huffman Coding\n";
    cout << "2. LZ77\n";
    cout << "3. Run-Length Encoding (RLE)\n";
    cout << "4. LZW\n";
    cout << "5. DEFLATE\n";
    cout << "6. Arithmetic Coding\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    string outputPath;

    switch (choice) {
        case 1:
            outputPath = removeExtension(inputPath) + ".huff";
            compressFile(inputPath.c_str(), outputPath.c_str());
            break;

        case 2: {
            outputPath = removeExtension(inputPath) + ".lz77";
            LZ77 lz77;
            lz77.compress(inputPath.c_str(), outputPath.c_str());
            break;
        }

        case 3:
            outputPath = removeExtension(inputPath) + ".rle";
            rleCompressFile(inputPath.c_str(), outputPath.c_str());
            break;

        case 4: {
            outputPath = removeExtension(inputPath) + ".lzw";
            Trie trie;
            LZW lzw;
            lzw.compress(inputPath, outputPath, trie);
            break;
        }

        case 5: {
            outputPath = removeExtension(inputPath) + ".deflate";
            Deflate deflate;
            deflate.compress(inputPath.c_str(), outputPath.c_str());
            break;
        }

        case 6: {
            outputPath = removeExtension(inputPath) + ".arc";
            ArithmeticCoding ac;
            ac.compress(inputPath.c_str(), outputPath.c_str());
            break;
        }

        default:
            cout << "Invalid choice.\n";
            return;
    }

    if (fs::exists(outputPath))
        cout << "Compression successful.\nSaved as: " << outputPath << "\n";
    else
        cout << "Compression failed.\n";
}

// ------------------------------------------------------------
// Decompression Dispatcher
// ------------------------------------------------------------
void decompressFileCLI(const string& inputPath) {
    string ext = fs::path(inputPath).extension().string();
    string outputPath = removeExtension(inputPath) + "_decompressed.txt";

    if (ext == ".huff") {
        decompressFile(inputPath.c_str(), outputPath.c_str());
    }
    else if (ext == ".lz77") {
        LZ77 lz77;
        lz77.decompress(inputPath.c_str(), outputPath.c_str());
    }
    else if (ext == ".rle") {
        rleDecompressFile(inputPath.c_str(), outputPath.c_str());
    }
    else if (ext == ".lzw") {
        HashTable table(1024);
        LZW lzw;
        lzw.decompress(inputPath, outputPath, table);
    }
    else if (ext == ".deflate") {
        Deflate deflate;
        deflate.decompress(inputPath.c_str(), outputPath.c_str());
    }
    else if (ext == ".arc") {
        ArithmeticCoding ac;
        ac.decompress(inputPath.c_str(), outputPath.c_str());
    }
    else {
        cout << "Unsupported compressed file format.\n";
        return;
    }

    if (fs::exists(outputPath))
        cout << "Decompression successful.\nSaved as: " << outputPath << "\n";
    else
        cout << "Decompression failed.\n";
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------
int main() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "=== File Compression System ===\n";
    cout << "Enter file path: ";

    string inputPath;
    getline(cin, inputPath);

    if (!fs::exists(inputPath)) {
        cout << "File does not exist.\n";
        return 1;
    }

    string ext = fs::path(inputPath).extension().string();

    if (ext == ".txt") {
        compressFileCLI(inputPath);
    }
    else {
        decompressFileCLI(inputPath);
    }

    return 0;
}
