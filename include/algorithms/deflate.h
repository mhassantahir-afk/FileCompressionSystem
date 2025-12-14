//
// Created by Mrjoe on 12/15/2025.
//
#ifndef DEFLATE_H
#define DEFLATE_H

class Deflate {
public:
    // Compress a file using Deflate (LZ77 + Huffman)
    void compress(const char* inputFile, const char* outputFile);

    // Decompress a file compressed with Deflate
    void decompress(const char* inputFile, const char* outputFile);

private:
    // Temporary file names for intermediate steps
    static const char* LZ77_TEMP_FILE;
};

#endif // DEFLATE_H