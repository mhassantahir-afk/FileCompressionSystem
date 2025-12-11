#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LLNode.h"

class Linkedlist {
public:
    LLNode* head;

    // Constructor
    Linkedlist();

    // Insertion methods
    void insertAtStart(int val);
    void insertAtEnd(int val);
    void insertAtPos(int pos, int val);

    // Removal methods
    void removeAtStart();
    void removeAtEnd();
    void removeAtPos(int pos);

    // Display method
    void Display();
};

#endif // LINKEDLIST_H