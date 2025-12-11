//
//  main.cpp
//  circularlinklist
//
//  Created by Huzaifa Rauf on 21/10/2025.
//

#include <iostream>
using namespace std;

class CLLNode {
public:
    int data;
    CLLNode* next;

    CLLNode(int val) {
        data = val;
        next = nullptr;
    }
};

class CircularLinkList{
public:
    CLLNode *head;
    CircularLinkList(){
        head = nullptr;
    }
    
    void InsertAtStart(int val){
        CLLNode *newNode = new CLLNode(val);
        if (head == nullptr) {
                    head = newNode;
                    newNode->next = head;
                    return;
                }
        CLLNode *temp = head;
        while(temp->next != head){
            temp = temp->next;
        }
        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }
    
    void insertAtEnd(int val){
        CLLNode *newNode = new CLLNode(val);
        if(head == nullptr){
            head = newNode;
            newNode->next = head;
            return;
        }
        
        CLLNode *temp = head;
        while(temp->next != head){
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
    
    void insertAtPos(int val, int pos) {
        CLLNode *newNode = new CLLNode(val);

        if (head == nullptr) {
            if (pos == 1) {
                head = newNode;
                newNode->next = head;
            } else {
                cout << "Invalid position\n";
                delete newNode;
            }
            return;
        }

        if (pos == 1) {
            InsertAtStart(val);
            return;
        }

        CLLNode *temp = head;
        int count = 1;

        while (count < pos - 1 && temp->next != head) {
            temp = temp->next;
            count++;
        }

        if (count != pos - 1) {
            cout << "Invalid position\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    
    void removeAtStart(){
        if(head == nullptr){
            cout << "list empty\n";
            return;
        }
        CLLNode *temp = head;
        while(temp->next != head){
            temp = temp->next;
        }
        CLLNode *del = head;
        head = head->next;
        temp->next = head;
        delete del;
    }
    
    void removeAtEnd(){
        if(head == nullptr){
            cout << "list empty\n";
            return;
        }
        CLLNode *temp = head;
        while(temp->next->next != head){
            temp = temp->next;
        }
        CLLNode *del = temp->next;
        temp->next = head;
        delete del;
    }
    
    void removeAtPos(int pos) {
        if (head == nullptr) {
            cout << "list empty\n";
            return;
        }

        if (pos == 1) {
            removeAtStart();
            return;
        }

        CLLNode *temp = head;
        int count = 1;

        while (count < pos - 1 && temp->next != head) {
            temp = temp->next;
            count++;
        }

        if (temp->next == head || count != pos - 1) {
            cout << "Invalid position\n";
            return;
        }

        CLLNode *del = temp->next;
        temp->next = del->next;
        delete del;
    }

    
    void Display(){
        CLLNode *temp = head;
        do{
            cout << temp->data << " ";
            temp = temp->next;
        }while(temp != head);
        cout << endl;
    }
};
