//
// Created by Mrjoe on 12/14/2025.
//
#ifndef LZ77_H
#define LZ77_H

class LZ77 {
public:
    static const int WINDOW_SIZE = 1024;
    static const int LOOKAHEAD_SIZE = 32;

    struct Token {
        unsigned short offset;
        unsigned short length;
        unsigned char next;
    };

    // Add character to sliding window
    void addToWindow(unsigned char window[], int &windowSize, unsigned char c);

    // Compress a file using LZ77 algorithm
    void compress(const char* input, const char* output);

    // Decompress a file compressed with LZ77
    void decompress(const char* input, const char* output);
};

#endif // LZ77_H