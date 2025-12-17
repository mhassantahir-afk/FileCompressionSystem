/*
 * Huzaifa Rauf
 * LZ77 Algorithms
 */

#include "algorithms/lz77.h"
#include "utils/FileIO.h"
#include <iostream>
#include <vector>
using namespace std;

void LZ77::addToWindow(unsigned char window[], int &windowSize, unsigned char c) {
    if (windowSize < WINDOW_SIZE) {
        window[windowSize++] = c;
    } else {
        for (int i = 0; i < WINDOW_SIZE - 1; i++)
            window[i] = window[i + 1];
        window[WINDOW_SIZE - 1] = c;
    }
}

void LZ77::compress(const char* input, const char* output) {
    vector<unsigned char> buffer = FileIO::readFileBinary(input);
    if (buffer.empty()) {
        cout << "Empty file or cannot read!" << endl;
        return;
    }

    ofstream fout = FileIO::openOutputFile(output);
    if (!fout) {
        return;
    }

    int pos = 0;
    while (pos < buffer.size()) {
        int bestLength = 0;
        int bestOffset = 0;
        int windowStart = max(0, pos - WINDOW_SIZE);

        for (int i = windowStart; i < pos; i++) {
            int length = 0;
            while (length < LOOKAHEAD_SIZE &&
                   pos + length < buffer.size() &&
                   buffer[i + length] == buffer[pos + length]) {
                length++;
            }

            if (length > bestLength) {
                bestLength = length;
                bestOffset = pos - i;
            }
        }

        Token token;
        token.offset = bestOffset;
        token.length = bestLength;
        token.next = (pos + bestLength < buffer.size()) ? buffer[pos + bestLength] : 0;

        fout.write(reinterpret_cast<const char*>(&token), sizeof(Token));
        pos += bestLength + 1;
    }

    fout.close();
}

void LZ77::decompress(const char* input, const char* output) {
    ifstream fin = FileIO::openInputFile(input);
    if (!fin) {
        return;
    }

    vector<unsigned char> output_buffer;
    Token token;

    while (fin.read(reinterpret_cast<char*>(&token), sizeof(Token))) {
        if (token.length > 0 && token.offset > 0) {
            int start = output_buffer.size() - token.offset;
            if (start < 0) {
                cerr << "Error: Invalid offset!" << endl;
                break;
            }

            for (int i = 0; i < token.length; i++) {
                output_buffer.push_back(output_buffer[start + i]);
            }
        }

        if (token.next != 0 || token.length > 0 || token.offset > 0) {
            output_buffer.push_back(token.next);
        }
    }

    fin.close();
    FileIO::writeFileBinary(output, output_buffer);
}