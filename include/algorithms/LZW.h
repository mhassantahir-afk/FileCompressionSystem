//
// Created by Mrjoe on 12/15/2025.
//
#ifndef LZW_H
#define LZW_H

#include <string>
#include "datastructures/Trie.h"
#include "datastructures/HashTable.h"

class LZW {
public:
    // Compress a file using LZW algorithm
    void compress(const std::string& inputFile, const std::string& outputFile, Trie& trie);

    // Decompress a file using LZW algorithm
    void decompress(const std::string& inputFile, const std::string& outputFile, HashTable& table);
};

#endif // LZW_H