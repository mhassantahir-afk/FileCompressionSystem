//
// Created by Mrjoe on 12/15/2025.
//
#include "algorithms/Deflate.h"
#include "algorithms/lz77.h"
#include "algorithms/huffman.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* Deflate::LZ77_TEMP_FILE = "temp_lz77.tmp";

void Deflate::compress(const char* inputFile, const char* outputFile) {
    // STEP 1: LZ77 Compression - USE EXISTING LZ77 CLASS
    LZ77 lz77;
    lz77.compress(inputFile, LZ77_TEMP_FILE);

    // STEP 2: Read LZ77 output
    ifstream lz77File(LZ77_TEMP_FILE, ios::binary);
    if (!lz77File) {
        cerr << "Error: Cannot read LZ77 temporary file!" << endl;
        return;
    }

    string lz77Data((istreambuf_iterator<char>(lz77File)), istreambuf_iterator<char>());
    lz77File.close();

    if (lz77Data.empty()) {
        cerr << "Error: LZ77 output is empty!" << endl;
        return;
    }

    // STEP 3: Apply Huffman coding - USE EXISTING HUFFMAN FUNCTIONS

    // Count character frequencies
    int freq[256] = {0};
    for (char c : lz77Data) {
        freq[(unsigned char)c]++;
    }

    // Build frequency arrays
    char data[256];
    int freqArray[256];
    int uniqueChars = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[uniqueChars] = (char)i;
            freqArray[uniqueChars] = freq[i];
            uniqueChars++;
        }
    }

    // USE EXISTING HUFFMAN FUNCTIONS
    HuffmanNode* root = buildHuffmanTree(data, freqArray, uniqueChars);

    char codes[256][MAX_TREE_HT] = {0};
    int codeLen[256] = {0};
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0, codes, codeLen);

    int encodedLen;
    char* encoded = encode(lz77Data.c_str(), lz77Data.length(), codes, &encodedLen);

    // STEP 4: Write final compressed file
    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error: Cannot create output file!" << endl;
        delete[] encoded;
        return;
    }

    // Write metadata
    int originalLen = lz77Data.length();
    outFile.write((char*)&originalLen, sizeof(int));
    outFile.write((char*)&encodedLen, sizeof(int));

    // USE EXISTING HUFFMAN FUNCTION
    saveTree(root, outFile);

    // Write encoded data
    for (int i = 0; i < encodedLen; i += 8) {
        unsigned char byte = 0;
        for (int j = 0; j < 8 && i + j < encodedLen; j++) {
            if (encoded[i + j] == '1') {
                byte |= (1 << (7 - j));
            }
        }
        outFile.put(byte);
    }

    outFile.close();
    delete[] encoded;

    // Clean up temporary file
    remove(LZ77_TEMP_FILE);

    // Get file sizes for statistics
    ifstream origFile(inputFile, ios::binary | ios::ate);
    int origSize = origFile.tellg();
    origFile.close();

    ifstream compFile(outputFile, ios::binary | ios::ate);
    int compSize = compFile.tellg();
    compFile.close();
}

void Deflate::decompress(const char* inputFile, const char* outputFile) {

    // STEP 1: Read compressed file and apply Huffman decoding


    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Error: Cannot open input file!" << endl;
        return;
    }

    // Read metadata
    int originalLen, encodedLen;
    inFile.read((char*)&originalLen, sizeof(int));
    inFile.read((char*)&encodedLen, sizeof(int));

    // USE EXISTING HUFFMAN FUNCTION
    HuffmanNode* root = loadTree(inFile);

    // Read encoded data
    char* encoded = new char[encodedLen + 1];
    int pos = 0;
    char byte;
    while (inFile.get(byte) && pos < encodedLen) {
        for (int i = 7; i >= 0 && pos < encodedLen; i--) {
            encoded[pos++] = ((byte >> i) & 1) ? '1' : '0';
        }
    }
    encoded[encodedLen] = '\0';
    inFile.close();

    // USE EXISTING HUFFMAN FUNCTION
    char* decoded = decode(root, encoded, originalLen);
    delete[] encoded;

    // Write LZ77 data to temporary file
    ofstream lz77TempFile(LZ77_TEMP_FILE, ios::binary);
    lz77TempFile.write(decoded, originalLen);
    lz77TempFile.close();
    delete[] decoded;

    // STEP 2: Apply LZ77 decompression - USE EXISTING LZ77 CLASS
    LZ77 lz77;
    lz77.decompress(LZ77_TEMP_FILE, outputFile);

    // Clean up temporary file
    remove(LZ77_TEMP_FILE);
}
