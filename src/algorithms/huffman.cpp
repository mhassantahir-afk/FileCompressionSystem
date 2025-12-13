#include <iostream>
#include <fstream>
#include <cstring>
#define MAX_TREE_HT 256

using namespace std;

// Huffman Tree Node
struct Node {
    char data;
    int freq;
    Node *left, *right;
};

// Min Heap Node
struct MinHeap {
    int size;
    int capacity;
    Node** array;
};

// Create a new tree node
Node* newNode(char data, int freq) {
    Node* temp = new Node;
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Create a min heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = new MinHeap;
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = new Node*[capacity];
    return minHeap;
}

// Swap two nodes
void swapNode(Node** a, Node** b) {
    Node* t = *a;
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
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Insert a node into min heap
void insertMinHeap(MinHeap* minHeap, Node* node) {
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

// Check if node is leaf
bool isLeaf(Node* root) {
    return !(root->left) && !(root->right);
}

// Create and build min heap
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Build Huffman Tree
Node* buildHuffmanTree(char data[], int freq[], int size) {
    Node *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Store Huffman codes
void storeCodes(Node* root, int arr[], int top, char codes[][MAX_TREE_HT], int codeLen[]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, codes, codeLen);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, codes, codeLen);
    }

    if (isLeaf(root)) {
        int idx = (unsigned char)root->data;
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
char* decode(Node* root, const char* encoded, int textLen) {
    char* decoded = new char[textLen + 1];
    int pos = 0;
    Node* curr = root;

    for (int i = 0; encoded[i] != '\0' && pos < textLen; i++) {
        curr = (encoded[i] == '0') ? curr->left : curr->right;

        if (isLeaf(curr)) {
            decoded[pos++] = curr->data;
            curr = root;
        }
    }

    decoded[pos] = '\0';
    return decoded;
}

// Compress file
void compressFile(const char* inputFile, const char* outputFile);

// Decompress file
void decompressFile(const char* inputFile, const char* outputFile);
