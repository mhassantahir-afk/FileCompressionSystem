#include <fstream>
#include <string>
using namespace std;

class LZW {
public:
    void compress(const string& inputFile, const string& outputFile, Trie& trie) {
        ifstream in(inputFile, ios::binary);
        ofstream out(outputFile, ios::binary);

        for (int i = 0; i < 256; i++) {
            string s = "";
            s += char(i);
            trie.insertAndGetIndex(s);
        }

        string p = "", c = "";
        char ch;

        if (!in.get(ch))
            return;

        p += ch;

        while (in.get(ch)) {
            c = ch;
            if (trie.search(p + c) != -1) {
                p = p + c;
            } else {
                int code = trie.search(p);
                out.write((char*)&code, sizeof(code));
                trie.insertAndGetIndex(p + c);
                p = c;
            }
        }

        int code = trie.search(p);
        out.write((char*)&code, sizeof(code));

        in.close();
        out.close();
    }

    void decompress(const string& inputFile, const string& outputFile, HashTable& table) {
        ifstream in(inputFile, ios::binary);
        ofstream out(outputFile, ios::binary);

        int nextCode = 1;
        for (int i = 0; i < 256; i++) {
            string s = "";
            s += char(i);
            table.insertKey(to_string(nextCode++), s);
        }

        int oldCode, newCode;
        if (!in.read((char*)&oldCode, sizeof(oldCode)))
            return;

        string s = table.searchKey(to_string(oldCode));
        out << s;

        string c = "";
        c += s[0];

        while (in.read((char*)&newCode, sizeof(newCode))) {
            string entry = table.searchKey(to_string(newCode));
            if (entry == "")
                entry = s + c;

            out << entry;
            c = entry[0];
            table.insertKey(to_string(nextCode++), s + c);
            s = entry;
        }

        in.close();
        out.close();
    }
};
