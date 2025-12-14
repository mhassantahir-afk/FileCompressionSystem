// MUbashir Ali
// DSA project
#include <string>
#include <iostream>
#include"datastructures/Trie.h"
#include"datastructures/TrieNode.h"

using namespace std;

TrieNode::TrieNode() {
        index = -1;           
        for (int i = 0; i < 256; i++)
            child[i] = NULL;
}

Trie::Trie() {
        root = new TrieNode();
        nextIndex = 1;         
    }

    // Insert a string (used in LZW/LZ78 dictionary building)
    int Trie::insertAndGetIndex(const string &s) {
        TrieNode* current = root;

        for (int i = 0; i < s.length(); i++) {
            unsigned char c = s[i];

            if (current->child[c] == NULL)
                current->child[c] = new TrieNode();

            current = current->child[c];
        }

        // assign dictionary index if not already assigned
        if (current->index == -1)
            current->index = nextIndex++;

        return current->index;
    }

    // Check if a string already exists (returns index)
    int Trie::search(const string& s) {
        TrieNode* current = root;

        for (int i = 0; i < s.length(); i++) {
            unsigned char c = s[i];

            if (current->child[c] == NULL)
                return -1;

            current = current->child[c];
        }

        return current->index;
    }

    // Longest prefix used in LZW compression
    int Trie::longestPrefix(const string& text, int start, int& lengthOut) {
        TrieNode* current = root;
        int lastIndex = -1;
        lengthOut = 0;

        for (int i = start; i < text.length(); i++) {
            unsigned char c = text[i];

            if (current->child[c] == NULL)
                break;

            current = current->child[c];
            lengthOut++;

            if (current->index != -1)
                lastIndex = current->index;   // longest valid match so far
        }

        return lastIndex; // returns dictionary code
    }

    // Print entire dictionary (optional)
    void Trie::printAll(TrieNode* node, string prefix) {
        if (!node) return;

        if (node->index != -1)
            cout << node->index << " : " << prefix << endl;

        for (int i = 0; i < 256; i++) {
            if (node->child[i] != NULL)
                printAll(node->child[i], prefix + char(i));
        }
    }

    void Trie::printDictionary() {
        printAll(root, "");
    }