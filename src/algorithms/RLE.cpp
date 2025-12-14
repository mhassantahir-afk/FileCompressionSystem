// Mubashir
//DSA project (14 dec )
#include "algorithms/RLE.h"
#include <iostream>
#include <fstream>

using namespace std;

//#define MAX_RUN 255

void rleCompressFile(const char* inputFile, const char* outputFile) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    if (!in || !out) {
        cout << "File error\n";
        return;
    }

    char prev, curr;
    unsigned char count = 1;

    in.get(prev);

    while (in.get(curr)) {
        if (curr == prev && count < MAX_RUN) {
            count++;
        } else {
            out.write((char*)&count, 1);
            out.write(&prev, 1);
            prev = curr;
            count = 1;
        }
    }

    out.write((char*)&count, 1);
    out.write(&prev, 1);

    in.close();
    out.close();

    cout << "RLE Compression Complete\n";
}

void rleDecompressFile(const char* inputFile, const char* outputFile) {
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    if (!in || !out) {
        cout << "File error\n";
        return;
    }

    unsigned char count;
    char ch;

    while (in.read((char*)&count, 1) && in.read(&ch, 1)) {
        for (int i = 0; i < count; i++)
            out.write(&ch, 1);
    }

    in.close();
    out.close();

    cout << "RLE Decompression Complete\n";
}

void analyzeFileForRLE(const char* inputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in) {
        cout << "File error\n";
        return;
    }

    char prev, curr;
    int fileSize = 0, totalRuns = 0, longRuns = 0, maxRun = 0, count = 1;

    in.get(prev);
    fileSize++;

    while (in.get(curr)) {
        fileSize++;
        if (curr == prev) {
            count++;
        } else {
            totalRuns++;
            if (count >= 3) longRuns++;
            if (count > maxRun) maxRun = count;
            prev = curr;
            count = 1;
        }
    }

    totalRuns++;
    if (count >= 3) longRuns++;
    if (count > maxRun) maxRun = count;

    in.close();

    cout << "\nFile size: " << fileSize << " bytes\n";
    cout << "Total runs: " << totalRuns << "\n";
    cout << "Max run length: " << maxRun << "\n";

    if (longRuns > totalRuns / 3)
        cout << "RLE suitable\n";
    else
        cout << "Use Huffman\n";
}
