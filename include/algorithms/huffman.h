//
// Created by Mrjoe on 12/13/2025.
//
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include "datastructures/HuffmanNode.h"
#define MAX_TREE_HT 256

// Huffman helper functions - exposed for use by other algorithms
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size);
void storeCodes(HuffmanNode* root, int arr[], int top, char codes[][MAX_TREE_HT], int codeLen[]);
char* encode(const char* text, int textLen, char codes[][MAX_TREE_HT], int* encodedLen);
char* decode(HuffmanNode* root, const char* encoded, int textLen);
void saveTree(HuffmanNode* root, std::ofstream& outFile);
HuffmanNode* loadTree(std::ifstream& inFile);

// Main compression functions
void compressFile(const char* inputFile, const char* outputFile);
void decompressFile(const char* inputFile, const char* outputFile);

#endif // HUFFMAN_H