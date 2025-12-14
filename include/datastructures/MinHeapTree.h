#ifndef MINHEAPTREE_H
#define MINHEAPTREE_H

#include "HuffmanNode.h"

class MinHeapTree {
public:
    HuffmanNode* heap[1000];
    int size;

    MinHeapTree();

    void insert(HuffmanNode* currentNode);
    HuffmanNode* extractMin();
    int getSize();
    void printHeap();

private:
    void swap(int i, int j);
    void heapifyDown(int i);
    void heapifyUp(int i);
};

#endif // MINHEAPTREE_H