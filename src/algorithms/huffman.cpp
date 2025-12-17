/*
 * Hassan Tahir
 * Huffman Coding
 */

#include <iostream>
#include <vector>
#include "datastructures/HuffmanNode.h"
#include "datastructures/MinHeapTree.h"
#include "algorithms/huffman.h"
#include "utils/FileIO.h"
#define MAX_TREE_HT 256

using namespace std;

// Build Huffman Tree using MinHeapTree
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeapTree minHeap;

    for (int i = 0; i < size; i++) {
        minHeap.insert(new HuffmanNode(data[i], freq[i]));
    }

    while (minHeap.getSize() > 1) {
        HuffmanNode* left = minHeap.extractMin();
        HuffmanNode* right = minHeap.extractMin();
        HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.insert(top);
    }

    return minHeap.extractMin();
}

// Store Huffman codes
void storeCodes(HuffmanNode* root, int arr[], int top, char codes[][MAX_TREE_HT], int codeLen[]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, codes, codeLen);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, codes, codeLen);
    }

    if (root->isLeaf()) {
        int idx = (unsigned char)root->ch;
        codeLen[idx] = top;
        for (int i = 0; i < top; i++)
            codes[idx][i] = arr[i] + '0';
        codes[idx][top] = '\0';
    }
}

// Encode text
char* encode(const char* text, int textLen, char codes[][MAX_TREE_HT], int* encodedLen) {
    char* encoded = new char[textLen * MAX_TREE_HT];
    int pos = 0;

    for (int i = 0; i < textLen; i++) {
        int idx = (unsigned char)text[i];
        int j = 0;
        while (codes[idx][j] != '\0')
            encoded[pos++] = codes[idx][j++];
    }

    encoded[pos] = '\0';
    *encodedLen = pos;
    return encoded;
}

// Decode text
char* decode(HuffmanNode* root, const char* encoded, int textLen) {
    char* decoded = new char[textLen + 1];
    int pos = 0;
    HuffmanNode* curr = root;

    for (int i = 0; encoded[i] != '\0' && pos < textLen; i++) {
        curr = (encoded[i] == '0') ? curr->left : curr->right;

        if (curr->isLeaf()) {
            decoded[pos++] = curr->ch;
            curr = root;
        }
    }

    decoded[pos] = '\0';
    return decoded;
}

// Save Huffman tree structure to file
void saveTree(HuffmanNode* root, ofstream& outFile) {
    if (root == nullptr) return;

    if (root->isLeaf()) {
        FileIO::writeChar(outFile, '1');
        FileIO::writeChar(outFile, root->ch);
    } else {
        FileIO::writeChar(outFile, '0');
        saveTree(root->left, outFile);
        saveTree(root->right, outFile);
    }
}

// Load Huffman tree structure from file
HuffmanNode* loadTree(ifstream& inFile) {
    char marker = FileIO::readChar(inFile);

    if (marker == '1') {
        char ch = FileIO::readChar(inFile);
        return new HuffmanNode(ch, 0);
    } else {
        HuffmanNode* node = new HuffmanNode('$', 0);
        node->left = loadTree(inFile);
        node->right = loadTree(inFile);
        return node;
    }
}

// Compress file
void compressFile(const char* inputFile, const char* outputFile) {
    string content = FileIO::readFileString(inputFile);
    if (content.empty()) {
        cerr << "Error: Input file is empty or cannot be read: " << inputFile << endl;
        return;
    }

    int freq[256] = {0};
    for (char c : content) {
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

    if (uniqueChars == 0) {
        cerr << "Error: No characters to compress" << endl;
        return;
    }

    HuffmanNode* root = buildHuffmanTree(data, freqArray, uniqueChars);

    char codes[256][MAX_TREE_HT] = {0};
    int codeLen[256] = {0};
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0, codes, codeLen);

    int encodedLen;
    char* encoded = encode(content.c_str(), content.length(), codes, &encodedLen);

    ofstream outFile = FileIO::openOutputFile(outputFile);
    if (!outFile) {
        delete[] encoded;
        return;
    }

    int originalLen = content.length();
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
}

// Decompress file
void decompressFile(const char* inputFile, const char* outputFile) {
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

    vector<unsigned char> outputData(decoded, decoded + originalLen);
    FileIO::writeFileBinary(outputFile, outputData);

    delete[] encoded;
    delete[] decoded;
}