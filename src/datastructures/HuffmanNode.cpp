//
// Created by Mrjoe on 12/11/2025.
//
class HuffmanNode
{
public:
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};