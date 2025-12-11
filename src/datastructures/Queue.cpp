// Mubashar Ali
//DSA project
class Queue {
public:
    QNode* front;
    QNode* rear;

    Queue() {
        front = rear = NULL;
    }

    bool isEmpty() {
        return front == NULL;
    }

    void enqueue(HuffmanNode* x) {
        QNode* temp = new QNode(x);
        if(isEmpty()) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
    }

    HuffmanNode* dequeue() {
        if(isEmpty()) return NULL;

        QNode* temp = front;
        HuffmanNode* data = temp->data;

        front = front->next;
        if(front == NULL) rear = NULL;

        delete temp;
        return data;
    }

    HuffmanNode* getFront() {
        return isEmpty() ? NULL : front->data;
    }

    void clear() {
        while(!isEmpty()) dequeue();
    }
};

#include <iostream>
using namespace std ;


class Queue {
public:
    QNode* front;
    QNode* rear;

    Queue() {
        front = rear = NULL;
    }

    bool isEmpty() {
        return front == NULL;
    }

    void enqueue(HuffmanNode* x) {
        QNode* temp = new QNode(x);
        if(isEmpty()) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
    }

    HuffmanNode* dequeue() {
        if(isEmpty()) return NULL;

        QNode* temp = front;
        HuffmanNode* data = temp->data;

        front = front->next;
        if(front == NULL) rear = NULL;

        delete temp;
        return data;
    }

    HuffmanNode* getFront() {
        return isEmpty() ? NULL : front->data;
    }

    void clear() {
        while(!isEmpty()) dequeue();
    }
};
