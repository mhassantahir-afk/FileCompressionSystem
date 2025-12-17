/*
 * Huzaifa Rauf
 * HashTable
 */
#include "datastructures/HashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;
    table = new Node*[capacity];

    // Initialize all buckets to nullptr
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clear();
    delete[] table;
}

int HashTable::hash(const string& key) {
    unsigned long hashValue = 0;

    // Simple polynomial rolling hash
    for (char c : key) {
        hashValue = hashValue * 31 + c;
    }

    return hashValue % capacity;
}

void HashTable::resize() {
    int oldCapacity = capacity;
    Node** oldTable = table;

    // Double the capacity
    capacity *= 2;
    table = new Node*[capacity];
    size = 0;

    // Initialize new table
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }

    // Rehash all entries
    for (int i = 0; i < oldCapacity; i++) {
        Node* current = oldTable[i];
        while (current != nullptr) {
            insert(current->key, current->value);
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    delete[] oldTable;
}

void HashTable::insert(const string& key, const string& value) {
    // Resize if load factor exceeds 0.75
    if (loadFactor() > 0.75) {
        resize();
    }

    int index = hash(key);
    Node* current = table[index];

    // Check if key already exists (update value)
    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    // Insert new node at the beginning of the chain
    Node* newNode = new Node(key, value);
    newNode->next = table[index];
    table[index] = newNode;
    size++;
}

string HashTable::get(const string& key) {
    int index = hash(key);
    Node* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    return "";  // Key not found
}

bool HashTable::remove(const string& key) {
    int index = hash(key);
    Node* current = table[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                // Remove first node in chain
                table[index] = current->next;
            } else {
                // Remove middle or last node
                prev->next = current->next;
            }
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }

    return false;  // Key not found
}

bool HashTable::contains(const string& key) {
    return !get(key).empty() || (get(key).empty() && table[hash(key)] != nullptr);
}

int HashTable::getSize() {
    return size;
}

int HashTable::getCapacity() {
    return capacity;
}

float HashTable::loadFactor() {
    return (float)size / capacity;
}

void HashTable::clear() {
    for (int i = 0; i < capacity; i++) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
    size = 0;
}

void HashTable::print() {
    cout << "\n=== Hash Table Contents ===" << endl;
    cout << "Size: " << size << ", Capacity: " << capacity << ", Load Factor: " << loadFactor() << endl;

    for (int i = 0; i < capacity; i++) {
        if (table[i] != nullptr) {
            cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                cout << "[" << current->key << ": " << current->value << "] ";
                current = current->next;
            }
            cout << endl;
        }
    }
    cout << "=========================" << endl;
}