#include <iostream>
#include <fstream>
#include <cstring>
#include "datastructures/HuffmanNode.h"
#define MAX_TREE_HT 256

using namespace std;

// Min Heap Node
struct MinHeap {
    int size;
    int capacity;
    HuffmanNode** array;
};

// Create a min heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = new MinHeap;
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = new HuffmanNode*[capacity];
    return minHeap;
}

// Swap two nodes
void swapNode(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify function
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Check if size is 1
bool isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Extract minimum node
HuffmanNode* extractMin(MinHeap* minHeap) {
    HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Insert a node into min heap
void insertMinHeap(MinHeap* minHeap, HuffmanNode* node) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// Build min heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Create and build min heap
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = new HuffmanNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Build Huffman Tree
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    HuffmanNode *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
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
char* encode(const char* text, char codes[][MAX_TREE_HT], int* encodedLen) {
    int len = strlen(text);
    char* encoded = new char[len * MAX_TREE_HT];
    int pos = 0;

    for (int i = 0; i < len; i++) {
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

    // Step 3: Build Huffman tree
    HuffmanNode* root = buildHuffmanTree(data, freqArray, uniqueChars);

    // Step 4: Generate Huffman codes
    char codes[256][MAX_TREE_HT] = {0};
    int codeLen[256] = {0};
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0, codes, codeLen);

    // Step 5: Encode the text
    int encodedLen;
    char* encoded = encode(content.c_str(), codes, &encodedLen);

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