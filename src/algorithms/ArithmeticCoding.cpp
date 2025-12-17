/*
 * Huzaifa Rauf
 * ArithmeticCoding
 */

#include "algorithms/ArithmeticCoding.h"
#include "utils/FileIO.h"
#include <iostream>
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

    ifstream fin = FileIO::openInputFile(filename);
    if (!fin) {
        fileSize = 0;
        return;
    }

    fileSize = 0;
    unsigned char ch;

    while (fin) {
        ch = FileIO::readChar(fin);
        if (fin) {
            freq[ch]++;
            fileSize++;
        }
    }

    fin.close();

    if (fileSize == 0) fileSize = 1;

    for (int i = 0; i < 256; i++) {
        freq[i] /= fileSize;
    }

    buildTable();
}

long double ArithmeticCoding::encodeFile(const char* filename) {
    ifstream fin = FileIO::openInputFile(filename);
    if (!fin) {
        return 0.0;
    }

    long double low = 0, high = 1;
    unsigned char ch;

    while (fin) {
        ch = FileIO::readChar(fin);
        if (fin) {
            long double range = high - low;
            high = low + range * table[ch].high;
            low = low + range * table[ch].low;
        }
    }

    fin.close();
    return (low + high) / 2;
}

void ArithmeticCoding::decodeToFile(long double code, int length, const char* outname) {
    ofstream fout = FileIO::openOutputFile(outname);
    if (!fout) {
        return;
    }

    for (int k = 0; k < length; k++) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (code >= table[i].low && code < table[i].high) {
                FileIO::writeChar(fout, (unsigned char)i);

                long double l = table[i].low;
                long double h = table[i].high;

                if (h - l > 0) {
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

    ofstream fout = FileIO::openOutputFile(output);
    if (!fout) {
        return;
    }

    for (int i = 0; i < 256; i++) {
        FileIO::writeInteger(fout, freq[i]);
    }

    FileIO::writeInteger(fout, length);
    FileIO::writeInteger(fout, encodedNumber);

    fout.close();
}

void ArithmeticCoding::decompress(const char* input, const char* output) {
    ifstream fin = FileIO::openInputFile(input);
    if (!fin) {
        return;
    }

    for (int i = 0; i < 256; i++) {
        freq[i] = FileIO::readInteger<long double>(fin);
    }

    int length = FileIO::readInteger<int>(fin);
    long double code = FileIO::readInteger<long double>(fin);

    fin.close();
    buildTable();
    decodeToFile(code, length, output);
}