/*
 * Mubashir Ali
 * LZW Algorithm
 */

#include <fstream>
#include <string>
#include "datastructures/Trie.h"
#include "datastructures/HashTable.h"
#include "algorithms/LZW.h"
#include "utils/FileIO.h"
using namespace std;

void LZW::compress(const string& inputFile, const string& outputFile, Trie& trie) {
    ifstream in = FileIO::openInputFile(inputFile);
    ofstream out = FileIO::openOutputFile(outputFile);

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
            FileIO::writeInteger(out, code);
            trie.insertAndGetIndex(p + c);
            p = c;
        }
    }

    int code = trie.search(p);
    FileIO::writeInteger(out, code);

    in.close();
    out.close();
}

void LZW::decompress(const string& inputFile, const string& outputFile, HashTable& table) {
    ifstream in = FileIO::openInputFile(inputFile);
    ofstream out = FileIO::openOutputFile(outputFile);

    int nextCode = 1;
    for (int i = 0; i < 256; i++) {
        string s = "";
        s += char(i);
        table.insert(to_string(nextCode++), s);
    }

    int oldCode, newCode;
    if (!in.read(reinterpret_cast<char*>(&oldCode), sizeof(oldCode)))
        return;

    string s = table.get(to_string(oldCode));
    out << s;

    string c = "";
    c += s[0];

    while (in.read(reinterpret_cast<char*>(&newCode), sizeof(newCode))) {
        string entry = table.get(to_string(newCode));
        if (entry == "")
            entry = s + c;

        out << entry;
        c = entry[0];
        table.insert(to_string(nextCode++), s + c);
        s = entry;
    }

    in.close();
    out.close();
}