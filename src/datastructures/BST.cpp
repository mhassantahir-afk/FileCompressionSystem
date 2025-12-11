//
//  main.cpp
//  binarySearchTree
//
//  Created by Huzaifa Rauf on 29/10/2025.
//

#include <iostream>
using namespace std;

class BSTNode{
public:
    int data;
    BSTNode *left;
    BSTNode *right;
    BSTNode(int val){
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Tree{
public:
    BSTNode *root;
    Tree(){
        root = nullptr;
    }
    
    BSTNode* insert(BSTNode* BSTNode, int val) {
        if(BSTNode == nullptr){
            return new BSTNode(val);
        }
        
        if(val < BSTNode->data){
            BSTNode->left = insert(BSTNode->left, val);
        }
        else if(val > BSTNode->data){
            BSTNode->right = insert(BSTNode->right, val);
        }
        return BSTNode;
    }
    void inorder(BSTNode* BSTNode) {
        if (BSTNode == nullptr){
            return;
        }
        
        inorder(BSTNode->left);
        cout << BSTNode->data << " ";
        inorder(BSTNode->right);
    }
    
    void postorder(BSTNode* BSTNode){
        if (BSTNode == nullptr){
            return;
        }
        
        postorder(BSTNode->left);
        postorder(BSTNode->right);
        cout << BSTNode->data << " ";
    }
    
    void preorder(BSTNode *BSTNode){
        if (BSTNode == nullptr){
            return;
        }
        
        cout << BSTNode->data << " ";
        preorder(BSTNode->left);
        preorder(BSTNode->right);
    }
    
    BSTNode* Delete(BSTNode *BSTNode, int val){
        if(BSTNode == nullptr){
            cout << "tree empty\n";
            return BSTNode;
        }
        
        if (val < BSTNode->data){
            BSTNode->left = Delete(BSTNode->left, val);
        }
        else if (val > BSTNode->data){
            BSTNode->right = Delete(BSTNode->right, val);
        }
        else{
            if (BSTNode->left == nullptr) {
                BSTNode* temp = BSTNode->right;
                delete BSTNode;
                return temp;
            }
            else if (BSTNode->right == nullptr) {
                BSTNode* temp = BSTNode->left;
                delete BSTNode;
                return temp;
            }
            BSTNode* temp = findMin(BSTNode->right);
            BSTNode->data = temp->data;
            BSTNode->right = Delete(BSTNode->right, temp->data);
        }
        return BSTNode;
    }
    
    BSTNode* findMin(BSTNode* BSTNode) {
        while (BSTNode && BSTNode->left != nullptr){
            BSTNode = BSTNode->left;
        }
        return BSTNode;
    }
};
