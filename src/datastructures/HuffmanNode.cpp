//
// Created by Mrjoe on 12/11/2025.
//
/*
 * Hassan Tahir
 * HuffmanNode
 */

#include "datastructures/HuffmanNode.h"

HuffmanNode::HuffmanNode(char c, int f) {
    ch = c;
    freq = f;
    left = right = nullptr;
}

// Check if node is leaf
bool HuffmanNode::isLeaf() const {
    return !(left) && !(right);
}