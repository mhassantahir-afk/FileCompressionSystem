//
// Created by Mrjoe on 12/15/2025.
//
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

class HashTable {
private:
    struct Node {
        std::string key;
        std::string value;
        Node* next;

        Node(const std::string& k, const std::string& v) : key(k), value(v), next(nullptr) {}
    };

    Node** table;
    int capacity;
    int size;

    // Hash function
    int hash(const std::string& key);

    // Resize the table when load factor is high
    void resize();

public:
    // Constructor
    HashTable(int initialCapacity = 100);

    // Destructor
    ~HashTable();

    // Insert or update a key-value pair
    void insert(const std::string& key, const std::string& value);

    // Get value by key (returns empty string if not found)
    std::string get(const std::string& key);

    // Remove a key-value pair
    bool remove(const std::string& key);

    // Check if key exists
    bool contains(const std::string& key);

    // Get current size
    int getSize();

    // Get current capacity
    int getCapacity();

    // Get load factor
    float loadFactor();

    // Clear all entries
    void clear();

    // Print all entries (for debugging)
    void print();
};

#endif // HASHTABLE_H