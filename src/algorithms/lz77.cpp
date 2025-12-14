#include "algorithms/lz77.h"
#include <iostream>
#include <fstream>
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
    ifstream fin(input, ios::binary);
    ofstream fout(output, ios::binary);

    if (!fin || !fout) {
        cerr << "Error opening files!" << endl;
        return;
    }

    // Read entire file into buffer
    vector<unsigned char> buffer;
    unsigned char ch;
    while (fin.read((char*)&ch, 1)) {
        buffer.push_back(ch);
    }
    fin.close();

    if (buffer.empty()) {
        cout << "Empty file!" << endl;
        fout.close();
        return;
    }

    int pos = 0;
    vector<unsigned char> window;

    while (pos < buffer.size()) {
        int bestLength = 0;
        int bestOffset = 0;

        // Search for longest match in the window
        int windowStart = max(0, pos - WINDOW_SIZE);

        for (int i = windowStart; i < pos; i++) {
            int length = 0;

            // Match as many characters as possible
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

        // Get the literal character
        if (pos + bestLength < buffer.size()) {
            token.next = buffer[pos + bestLength];
        } else {
            token.next = 0;
        }

        fout.write((char*)&token, sizeof(Token));

        // Move position forward
        pos += bestLength + 1;
    }

    fout.close();
    cout << "LZ77 Compression Complete" << endl;
    cout << "Original size: " << buffer.size() << " bytes" << endl;
}

void LZ77::decompress(const char* input, const char* output) {
    ifstream fin(input, ios::binary);
    ofstream fout(output, ios::binary);

    if (!fin || !fout) {
        cerr << "Error opening files!" << endl;
        return;
    }

    vector<unsigned char> output_buffer;
    Token token;

    while (fin.read((char*)&token, sizeof(Token))) {
        // Copy from previous output if there's a match
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

        // Add the literal character
        if (token.next != 0 || token.length > 0 || token.offset > 0) {
            output_buffer.push_back(token.next);
        }
    }

    // Write output buffer to file
    for (unsigned char c : output_buffer) {
        fout.write((char*)&c, 1);
    }

    fin.close();
    fout.close();

    cout << "LZ77 Decompression Complete" << endl;
    cout << "Decompressed size: " << output_buffer.size() << " bytes" << endl;
}