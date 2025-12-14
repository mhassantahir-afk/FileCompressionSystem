#include "algorithms/ArithmeticCoding.h"
#include <iostream>
#include <fstream>
using namespace std;

ArithmeticCoding::ArithmeticCoding() {
    size = 256;
    for (int i = 0; i < 256; i++) freq[i] = 1.0 / 256.0;
    buildTable();
}

void ArithmeticCoding::buildTable() {
    long double cumulative = 0;
    for (int i = 0; i < size; i++) {
        table[i].ch = (unsigned char)i;
        table[i].low = cumulative;
        table[i].high = cumulative + freq[i];
        cumulative += freq[i];
    }
}

void ArithmeticCoding::calculateFrequencies(const char* filename, int &fileSize) {
    for (int i = 0; i < 256; i++) freq[i] = 0;

    ifstream fin(filename, ios::binary);
    unsigned char ch;
    fileSize = 0;

    while (fin.read((char*)&ch, 1)) {
        freq[ch]++;
        fileSize++;
    }
    fin.close();

    if (fileSize == 0) fileSize = 1;

    for (int i = 0; i < 256; i++) freq[i] /= fileSize;

    buildTable();
}

long double ArithmeticCoding::encodeFile(const char* filename) {
    ifstream fin(filename, ios::binary);
    unsigned char ch;

    long double low = 0, high = 1;

    while (fin.read((char*)&ch, 1)) {
        long double range = high - low;
        high = low + range * table[ch].high;
        low = low + range * table[ch].low;
    }
    fin.close();

    return (low + high) / 2;
}

void ArithmeticCoding::decodeToFile(long double code, int length, const char* outname) {
    ofstream fout(outname, ios::binary);

    for (int k = 0; k < length; k++) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (code >= table[i].low && code < table[i].high) {
                unsigned char ch = (unsigned char)i;
                fout.write((char*)&ch, 1);

                long double l = table[i].low;
                long double h = table[i].high;

                if (h - l > 0) {  // Prevent division by zero
                    code = (code - l) / (h - l);
                } else {
                    cerr << "Error: Range became zero at position " << k << endl;
                }

                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "Error: Could not decode character at position " << k << endl;
            break;
        }
    }

    fout.close();
}

void ArithmeticCoding::compress(const char* input, const char* output) {
    int length = 0;
    calculateFrequencies(input, length);

    if (length == 0) {
        cerr << "Error: Input file is empty or couldn't be read!" << endl;
        return;
    }

    long double encodedNumber = encodeFile(input);

    cout << "Original file size: " << length << " bytes" << endl;
    cout << "Encoded number: " << encodedNumber << endl;

    ofstream fout(output, ios::binary);

    for (int i = 0; i < 256; i++)
        fout.write((char*)&freq[i], sizeof(long double));

    fout.write((char*)&length, sizeof(int));
    fout.write((char*)&encodedNumber, sizeof(long double));

    fout.close();
}

void ArithmeticCoding::decompress(const char* input, const char* output) {
    ifstream fin(input, ios::binary);

    for (int i = 0; i < 256; i++)
        fin.read((char*)&freq[i], sizeof(long double));

    int length;
    long double code;

    fin.read((char*)&length, sizeof(int));
    fin.read((char*)&code, sizeof(long double));

    fin.close();

    buildTable();

    decodeToFile(code, length, output);
}
