//
// Created by Hassan on 12/15/2025.
//
/*
 * Hassan Tahir
 * Hufffman Coding
 */
#include "algorithms/Deflate.h"
#include "algorithms/lz77.h"
#include "algorithms/huffman.h"
#include "utils/FileIO.h"
#include <iostream>
#include <vector>

using namespace std;

const char* Deflate::LZ77_TEMP_FILE = "temp_lz77.tmp";

void Deflate::compress(const char* inputFile, const char* outputFile) {
    // STEP 1: LZ77 Compression
    LZ77 lz77;
    lz77.compress(inputFile, LZ77_TEMP_FILE);

    // STEP 2: Read LZ77 output
    string lz77Data = FileIO::readFileString(LZ77_TEMP_FILE);
    if (lz77Data.empty()) {
        cerr << "Error: LZ77 output is empty!" << endl;
        return;
    }

    // STEP 3: Apply Huffman coding
    int freq[256] = {0};
    for (char c : lz77Data) {
        freq[(unsigned char)c]++;
    }

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

    HuffmanNode* root = buildHuffmanTree(data, freqArray, uniqueChars);

    char codes[256][MAX_TREE_HT] = {0};
    int codeLen[256] = {0};
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0, codes, codeLen);

    int encodedLen;
    char* encoded = encode(lz77Data.c_str(), lz77Data.length(), codes, &encodedLen);

    // STEP 4: Write final compressed file
    ofstream outFile = FileIO::openOutputFile(outputFile);
    if (!outFile) {
        delete[] encoded;
        return;
    }

    int originalLen = lz77Data.length();
    FileIO::writeInteger(outFile, originalLen);
    FileIO::writeInteger(outFile, encodedLen);

    saveTree(root, outFile);

    for (int i = 0; i < encodedLen; i += 8) {
        unsigned char byte = 0;
        for (int j = 0; j < 8 && i + j < encodedLen; j++) {
            if (encoded[i + j] == '1') {
                byte |= (1 << (7 - j));
            }
        }
        FileIO::writeChar(outFile, byte);
    }

    outFile.close();
    delete[] encoded;
    FileIO::deleteFile(LZ77_TEMP_FILE);
}

void Deflate::decompress(const char* inputFile, const char* outputFile) {
    ifstream inFile = FileIO::openInputFile(inputFile);
    if (!inFile) {
        return;
    }

    int originalLen = FileIO::readInteger<int>(inFile);
    int encodedLen = FileIO::readInteger<int>(inFile);

    HuffmanNode* root = loadTree(inFile);

    char* encoded = new char[encodedLen + 1];
    int pos = 0;
    unsigned char byte;

    while (inFile && pos < encodedLen) {
        byte = FileIO::readChar(inFile);
        for (int i = 7; i >= 0 && pos < encodedLen; i--) {
            encoded[pos++] = ((byte >> i) & 1) ? '1' : '0';
        }
    }
    encoded[encodedLen] = '\0';
    inFile.close();

    char* decoded = decode(root, encoded, originalLen);
    delete[] encoded;

    vector<unsigned char> tempData(decoded, decoded + originalLen);
    FileIO::writeFileBinary(LZ77_TEMP_FILE, tempData);
    delete[] decoded;

    LZ77 lz77;
    lz77.decompress(LZ77_TEMP_FILE, outputFile);

    FileIO::deleteFile(LZ77_TEMP_FILE);
}