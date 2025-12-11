#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
using namespace std;

class Trie {
public:
    TrieNode* root;
    int nextIndex;
    
    // Constructor
    Trie();
    
    // Insert a string and return its dictionary index (used in LZW/LZ78)
    int insertAndGetIndex(const string& s);
    
    // Search for a string and return its index (-1 if not found)
    int search(const string& s);
    
    // Find longest prefix match starting from a position in text
    int longestPrefix(const string& text, int start, int& lengthOut);
    
    // Print the entire dictionary
    void printDictionary();

private:
    // Helper function for recursive dictionary printing
    void printAll(TrieNode* node, string prefix);
};

#endif // TRIE_H