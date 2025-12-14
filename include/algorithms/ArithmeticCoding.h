//
// Created by Mrjoe on 12/13/2025.
//

//
// Created by Mrjoe on 12/13/2025.
//
#ifndef ARITHMETICCODING_H
#define ARITHMETICCODING_H

class ArithmeticCoding {
public:
    struct Symbol {
        unsigned char ch;
        long double low;
        long double high;
    };

    long double freq[256];
    Symbol table[256];
    int size;

    // Constructor
    ArithmeticCoding();

    // Build probability table
    void buildTable();

    // Calculate character frequencies from file
    void calculateFrequencies(const char* filename, int &fileSize);

    // Encode file to a single number
    long double encodeFile(const char* filename);

    // Decode number back to file
    void decodeToFile(long double code, int length, const char* outname);

    // Compress a file
    void compress(const char* input, const char* output);

    // Decompress a file
    void decompress(const char* input, const char* output);
};

#endif // ARITHMETICCODING_H