#ifndef TRIENODE_H
#define TRIENODE_H

class TrieNode {
public:
    int index;                 // dictionary index (LZW/LZ78 use this)
    TrieNode* child[256];      // ASCII children
    
    // Constructor
    TrieNode();
};

#endif // TRIENODE_H