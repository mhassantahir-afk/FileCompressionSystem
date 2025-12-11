#ifndef MINHEAPTREE_H
#define MINHEAPTREE_H

#include "HuffmanNode.h"

class MinHeapTree {
public:
    HuffmanNode* heap[1000];
    int size;

    // Constructor
    MinHeapTree();

    // Insert a HuffmanNode into the heap
    void insert(HuffmanNode* currentNode);

    // Remove and return the minimum element
    HuffmanNode* extractMin();

    // Get the current size of the heap
    int getSize();

    // Display heap contents
    void printHeap();

private:
    // Helper methods for maintaining heap property
    void swap(int i, int j);
    void heapifyDown(int i);
    void heapifyUp(int i);
};

#endif // MINHEAPTREE_H