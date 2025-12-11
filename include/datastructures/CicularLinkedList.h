#ifndef CIRCULARLINKLIST_H
#define CIRCULARLINKLIST_H

#include "CLLNode.h"

class CircularLinkList {
public:
    CLLNode* head;
    
    // Constructor
    CircularLinkList();
    
    // Insertion methods
    void InsertAtStart(int val);
    void insertAtEnd(int val);
    void insertAtPos(int val, int pos);
    
    // Removal methods
    void removeAtStart();
    void removeAtEnd();
    void removeAtPos(int pos);
    
    // Display method
    void Display();
};

#endif // CIRCULARLINKLIST_H