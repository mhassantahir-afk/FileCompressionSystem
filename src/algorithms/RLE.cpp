// Mubashir
// DSA project (14 dec )
/*
 * Mubashir Ali
 * RLE Algorithm
 */
#include "algorithms/RLE.h"
#include "utils/FileIO.h"

using namespace std;

void rleCompressFile(const char* inputFile, const char* outputFile) {
    ifstream in = FileIO::openInputFile(inputFile);
    ofstream out = FileIO::openOutputFile(outputFile);

    if (!in || !out) {
        return;
    }

    unsigned char prev, curr;
    unsigned char count = 1;

    prev = FileIO::readChar(in);

    while (in) {
        curr = FileIO::readChar(in);
        if (in) {
            if (curr == prev && count < MAX_RUN) {
                count++;
            } else {
                FileIO::writeChar(out, count);
                FileIO::writeChar(out, prev);
                prev = curr;
                count = 1;
            }
        }
    }

    FileIO::writeChar(out, count);
    FileIO::writeChar(out, prev);

    in.close();
    out.close();
}

void rleDecompressFile(const char* inputFile, const char* outputFile) {
    ifstream in = FileIO::openInputFile(inputFile);
    ofstream out = FileIO::openOutputFile(outputFile);

    if (!in || !out) {
        return;
    }

    unsigned char count;
    unsigned char ch;

    while (in) {
        count = FileIO::readChar(in);
        if (in) {
            ch = FileIO::readChar(in);
            for (int i = 0; i < count; i++) {
                FileIO::writeChar(out, ch);
            }
        }
    }

    in.close();
    out.close();
}

void analyzeFileForRLE(const char* inputFile) {
    ifstream in = FileIO::openInputFile(inputFile);
    if (!in) {
        return;
    }

    unsigned char prev, curr;
    int fileSize = 0, totalRuns = 0, longRuns = 0, maxRun = 0, count = 1;

    prev = FileIO::readChar(in);
    fileSize++;

    while (in) {
        curr = FileIO::readChar(in);
        if (in) {
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
    }

    totalRuns++;
    if (count >= 3) longRuns++;
    if (count > maxRun) maxRun = count;

    in.close();
}