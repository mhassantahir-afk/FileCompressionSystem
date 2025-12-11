#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

class HuffmanNode {
public:
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    
    // Constructor
    HuffmanNode(char c, int f);
};

#endif // HUFFMANNODE_H