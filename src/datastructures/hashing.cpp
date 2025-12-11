//Mubahir ali
// DSA project

#include <iostream>
#include <string>
using namespace std;

struct HashNode {
    string key;
    string value;
    HashNode* next;
    HashNode(string k, string v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTable {
private:
    static const int SIZE = 256;
    HashNode* table[SIZE];

    int hashFunction(const string& key) {
        unsigned int hash = 0;
        for (char c : key)
            hash = (hash * 31 + c) % SIZE;
        return hash % SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++)
            table[i] = nullptr;
    }

    void insertKey(string key, string value) {
        int index = hashFunction(key);
        HashNode* node = new HashNode(key, value);

        if (table[index] == nullptr)
            table[index] = node;
        else {
            HashNode* temp = table[index];
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = node;
        }
    }

    string searchKey(string key) {
        int index = hashFunction(key);
        HashNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->key == key)
                return temp->value;
            temp = temp->next;
        }
        return "";
    }

    bool deleteKey(string key) {
        int index = hashFunction(key);
        HashNode* temp = table[index];
        HashNode* prev = nullptr;

        while (temp != nullptr) {
            if (temp->key == key) {
                if (prev == nullptr)
                    table[index] = temp->next;
                else
                    prev->next = temp->next;
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }

        return false;
    }
};
