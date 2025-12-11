// MUbashir Ali
// DSA project

class TrieNode {
public:
    int index;                 // dictionary index (LZW/LZ78 use this)
    TrieNode* child[256];      // ASCII children

    TrieNode() {
        index = -1;           
        for (int i = 0; i < 256; i++)
            child[i] = NULL;
    }
};

class Trie {
public:
    TrieNode* root;
    int nextIndex;             

    Trie() {
        root = new TrieNode();
        nextIndex = 1;         
    }

    // Insert a string (used in LZW/LZ78 dictionary building)
    int insertAndGetIndex(const string& s) {
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
    int search(const string& s) {
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
    int longestPrefix(const string& text, int start, int& lengthOut) {
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
    void printAll(TrieNode* node, string prefix) {
        if (!node) return;

        if (node->index != -1)
            cout << node->index << " : " << prefix << endl;

        for (int i = 0; i < 256; i++) {
            if (node->child[i] != NULL)
                printAll(node->child[i], prefix + char(i));
        }
    }

    void printDictionary() {
        printAll(root, "");
    }
};
