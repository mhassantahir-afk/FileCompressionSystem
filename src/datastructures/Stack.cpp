//
//  main.cpp
//  Stack
//
//  Created by Huzaifa Rauf on 09/12/2025.
//

#include <iostream>
using namespace std;

class Stack {
public:
    int arr[100];
    int top;

    Stack() {
        top = -1;
    }

    void push(int val) {
        if (top == 99) {
            cout << "Stack overflow\n";
            return;
        }
        arr[++top] = val;
    }

    int pop() {
        if (top == -1) {
            cout << "Stack empty\n";
            return -1;
        }
        return arr[top--];
    }

    int peek() {
        if (top == -1) {
            cout << "Stack empty\n";
            return -1;
        }
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == 99;
    }

    int getSize() {
        return top + 1;
    }

    void display() {
        if (top == -1) {
            cout << "Stack empty\n";
            return;
        }
        for (int i = top; i >= 0; i--)
            cout << arr[i] << " ";
        cout << endl;
    }
};
