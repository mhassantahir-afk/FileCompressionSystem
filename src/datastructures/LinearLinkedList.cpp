//
//  main.cpp
//  dsalabassign2(fa24bse050)
//
//  Created by Huzaifa Rauf on 21/10/2025.
//

#include <iostream>
using namespace std;

class LLNode{
public:
    int data;
    LLNode *next;
    
    LLNode(int val){
        data = val;
        next = nullptr;
    }
};

class Linkedlist{
public:
    LLNode *head;
    
    Linkedlist(){
        head = nullptr;
    }
    
    void insertAtStart(int val){
        LLNode *newNode = new LLNode(val);
        if(head == nullptr){
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }
    
    void insertAtEnd(int val){
        LLNode *newNode = new LLNode(val);
        if(head == nullptr){
            head = newNode;
            return;
        }
        LLNode *temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }
    
    void insertAtPos(int pos, int val){
        LLNode *newNode = new LLNode(val);
        if(head == nullptr){
            head = newNode;
            return;
        }
        LLNode* temp = head;
        for(int i = 0; i<pos-1; i++){
            if(temp->next == nullptr){
                cout << "position invalid\n";
                return;
            }
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    
    void removeAtStart(){
        if(head == nullptr){
            cout << "list empty\n";
            return;
        }
        LLNode *temp = head;
        head = head->next;
        delete temp;
        
    }
    
    void removeAtEnd(){
        if(head == nullptr){
            cout << "list empty\n";
            return;
        }
        
        LLNode *temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        delete temp;
        temp = nullptr;
    }
    
    void removeAtPos(int pos){
        if(head == nullptr){
            cout << "list empty\n";
            return;
        }
        
        LLNode *temp = head;
        for(int i = 0; i < pos-1; i++){
            if(temp->next == nullptr){
                cout << "position invalid\n";
                return;
            }
            else{
                temp = temp->next;
            }
        }
        LLNode* del = temp->next;
        temp->next = del->next;
        delete del;

    }
    
    void Display(){
        if (head == nullptr){
            cout << "list is empty\n";
            return;
        }
        LLNode *tempo = head;
        while(tempo != nullptr){
            int info = tempo->data;
            cout << info << " ";
            tempo = tempo->next;
        }
        cout << endl;
    }
};
