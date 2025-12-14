//
//  main.cpp
//  lz77
//
//  Created by Huzaifa Rauf on 14/12/2025.
//
#include "algorithms/lz77.h"
#include <iostream>
#include <fstream>
using namespace std;

class LZ77 {
public:
    static const int WINDOW_SIZE = 1024;
    static const int LOOKAHEAD_SIZE = 32;

    struct Token {
        unsigned short offset;
        unsigned short length;
        unsigned char next;
    };

    void addToWindow(unsigned char window[], int &windowSize, unsigned char c) {
        if (windowSize < WINDOW_SIZE) {
            window[windowSize++] = c;
        } else {
            for (int i = 0; i < WINDOW_SIZE - 1; i++)
                window[i] = window[i + 1];
            window[WINDOW_SIZE - 1] = c;
        }
    }

    void compress(const char* input, const char* output) {
        ifstream fin(input, ios::binary);
        ofstream fout(output, ios::binary);

        unsigned char window[WINDOW_SIZE];
        unsigned char lookahead[LOOKAHEAD_SIZE];
        int windowSize = 0;

        while (!fin.eof()) {
            int lookSize = fin.read((char*)lookahead, LOOKAHEAD_SIZE).gcount();
            if (lookSize == 0) break;

            int bestLength = 0;
            int bestOffset = 0;

            for (int i = 0; i < windowSize; i++) {
                int length = 0;
                while (length < lookSize &&
                       i + length < windowSize &&
                       window[i + length] == lookahead[length]) {
                    length++;
                }
                if (length > bestLength) {
                    bestLength = length;
                    bestOffset = windowSize - i;
                }
            }

            Token token;
            token.offset = bestOffset;
            token.length = bestLength;
            token.next = lookahead[bestLength];

            fout.write((char*)&token, sizeof(Token));

            for (int i = 0; i <= bestLength; i++) {
                addToWindow(window, windowSize, lookahead[i]);
            }

            fin.seekg(bestLength + 1 - lookSize, ios::cur);
        }

        fin.close();
        fout.close();
    }

    void decompress(const char* input, const char* output) {
        ifstream fin(input, ios::binary);
        ofstream fout(output, ios::binary);

        unsigned char window[WINDOW_SIZE];
        int windowSize = 0;

        Token token;

        while (fin.read((char*)&token, sizeof(Token))) {
            if (token.offset == 0 && token.length == 0) {
                fout.write((char*)&token.next, 1);
                addToWindow(window, windowSize, token.next);
            } else {
                int start = windowSize - token.offset;
                for (int i = 0; i < token.length; i++) {
                    unsigned char c = window[start + i];
                    fout.write((char*)&c, 1);
                    addToWindow(window, windowSize, c);
                }
                fout.write((char*)&token.next, 1);
                addToWindow(window, windowSize, token.next);
            }
        }

        fin.close();
        fout.close();
    }
};
