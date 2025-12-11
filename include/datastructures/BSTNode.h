#ifndef NODE_H
#define NODE_H

class BSTNode {
public:
    int data;
    BSTNode* left;
    BSTNode* right;
    
    // Constructor
    BSTNode(int val);
};

#endif // NODE_H