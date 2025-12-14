#include <iostream>
#include <fstream>
#include <cstring>
#include "datastructures/HuffmanNode.h"
#include "datastructures/MinHeapTree.h"
#define MAX_TREE_HT 256

using namespace std;

// Build Huffman Tree using MinHeapTree
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeapTree minHeap;

    // Insert all characters into the heap
    for (int i = 0; i < size; i++) {
        minHeap.insert(new HuffmanNode(data[i], freq[i]));
    }

    // Build the tree
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

// Save Huffman tree structure to file (preorder traversal)
void saveTree(HuffmanNode* root, ofstream& outFile) {
    if (root == nullptr) return;

    if (root->isLeaf()) {
        outFile.put('1');  // Leaf node marker
        outFile.put(root->ch);  // Character
    } else {
        outFile.put('0');  // Internal node marker
        saveTree(root->left, outFile);
        saveTree(root->right, outFile);
    }
}

// Load Huffman tree structure from file
HuffmanNode* loadTree(ifstream& inFile) {
    char marker;
    inFile.get(marker);

    if (marker == '1') {  // Leaf node
        char ch;
        inFile.get(ch);
        return new HuffmanNode(ch, 0);
    } else {  // Internal node
        HuffmanNode* node = new HuffmanNode('$', 0);
        node->left = loadTree(inFile);
        node->right = loadTree(inFile);
        return node;
    }
}

// Compress file
void compressFile(const char* inputFile, const char* outputFile) {
    // Step 1: Read input file
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Error: Cannot open input file: " << inputFile << endl;
        return;
    }

    // Read entire file content
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    if (content.empty()) {
        cerr << "Error: Input file is empty" << endl;
        return;
    }

    // Step 2: Count character frequencies
    int freq[256] = {0};
    for (char c : content) {
        freq[(unsigned char)c]++;
    }

    // Count unique characters
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

    // Step 3: Build Huffman tree using MinHeapTree
    HuffmanNode* root = buildHuffmanTree(data, freqArray, uniqueChars);

    // Step 4: Generate Huffman codes
    char codes[256][MAX_TREE_HT] = {0};
    int codeLen[256] = {0};
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0, codes, codeLen);

    // Step 5: Encode the text
    int encodedLen;
    char* encoded = encode(content.c_str(), content.length(), codes, &encodedLen);

    // Step 6: Write to output file
    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error: Cannot open output file: " << outputFile << endl;
        delete[] encoded;
        return;
    }

    // Write original text length
    int originalLen = content.length();
    outFile.write((char*)&originalLen, sizeof(int));

    // Write encoded length
    outFile.write((char*)&encodedLen, sizeof(int));

    // Write tree structure
    saveTree(root, outFile);

    // Write encoded data (convert binary string to bytes)
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

    cout << "File compressed successfully!" << endl;
    cout << "Original size: " << originalLen << " bytes" << endl;
    cout << "Compressed size: " << (encodedLen / 8 + 1) << " bytes (approx)" << endl;
    cout << "Compression ratio: " << (float)encodedLen / (originalLen * 8) * 100 << "%" << endl;
}

// Decompress file
void decompressFile(const char* inputFile, const char* outputFile) {
    // Step 1: Read compressed file
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Error: Cannot open input file: " << inputFile << endl;
        return;
    }

    // Read original text length
    int originalLen;
    inFile.read((char*)&originalLen, sizeof(int));

    // Read encoded length
    int encodedLen;
    inFile.read((char*)&encodedLen, sizeof(int));

    // Step 2: Reconstruct Huffman tree
    HuffmanNode* root = loadTree(inFile);

    // Step 3: Read encoded data and convert to binary string
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

    // Step 4: Decode the data
    char* decoded = decode(root, encoded, originalLen);

    // Step 5: Write to output file
    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error: Cannot open output file: " << outputFile << endl;
        delete[] encoded;
        delete[] decoded;
        return;
    }

    outFile.write(decoded, originalLen);
    outFile.close();

    delete[] encoded;
    delete[] decoded;

    cout << "File decompressed successfully!" << endl;
    cout << "Decompressed size: " << originalLen << " bytes" << endl;
}
