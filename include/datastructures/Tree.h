#ifndef TREE_H
#define TREE_H

#include "BSTNode.h"

class Tree {
public:
    BSTNode* root;
    
    // Constructor
    Tree();
    
    // Insert a value into the BST
    BSTNode* insert(BSTNode* node, int val);
    
    // Tree traversal methods
    void inorder(BSTNode* node);
    void postorder(BSTNode* node);
    void preorder(BSTNode* node);
    
    // Delete a value from the BST
    BSTNode* Delete(BSTNode* node, int val);
    
    // Helper function to find minimum value node
    BSTNode* findMin(BSTNode* node);
};

#endif // TREE_H