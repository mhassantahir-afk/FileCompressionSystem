//
// Created by Mrjoe on 12/15/2025.
//
//
// Created for DSA Compression Project
//
#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
#include <fstream>

class FileIO {
public:
    // Read entire file as binary data
    static std::vector<unsigned char> readFileBinary(const std::string& filename);

    // Write binary data to file
    static bool writeFileBinary(const std::string& filename, const std::vector<unsigned char>& data);

    // Read entire file as string
    static std::string readFileString(const std::string& filename);

    // Write string to file
    static bool writeFileString(const std::string& filename, const std::string& data);

    // Open input file stream
    static std::ifstream openInputFile(const std::string& filename, std::ios_base::openmode mode = std::ios::binary);

    // Open output file stream
    static std::ofstream openOutputFile(const std::string& filename, std::ios_base::openmode mode = std::ios::binary);

    // Get file size
    static size_t getFileSize(const std::string& filename);

    // Check if file exists
    static bool fileExists(const std::string& filename);

    // Read a single integer from binary stream
    template<typename T>
    static T readInteger(std::ifstream& stream);

    // Write a single integer to binary stream
    template<typename T>
    static void writeInteger(std::ofstream& stream, T value);

    // Read character from binary stream
    static unsigned char readChar(std::ifstream& stream);

    // Write character to binary stream
    static void writeChar(std::ofstream& stream, unsigned char ch);

    // Create temporary file name
    static std::string getTempFileName(const std::string& prefix = "temp_");

    // Delete file
    static bool deleteFile(const std::string& filename);

    // Error handling
    static void handleFileError(const std::string& operation, const std::string& filename);
};

// Template implementation (must be in header)
template<typename T>
T FileIO::readInteger(std::ifstream& stream) {
    T value;
    stream.read(reinterpret_cast<char*>(&value), sizeof(T));
    return value;
}

template<typename T>
void FileIO::writeInteger(std::ofstream& stream, T value) {
    stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

#endif // FILEIO_H