//
// Created by Mrjoe on 12/14/2025.
//
#ifndef RLE_H
#define RLE_H

#define MAX_RUN 255

// Compress a file using Run-Length Encoding
void rleCompressFile(const char* inputFile, const char* outputFile);

// Decompress a file compressed with RLE
void rleDecompressFile(const char* inputFile, const char* outputFile);

// Analyze if a file is suitable for RLE compression
void analyzeFileForRLE(const char* inputFile);

#endif // RLE_H