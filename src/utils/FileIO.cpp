//
// Created by Mrjoe on 12/15/2025.
//
#include "utils/FileIO.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>

using namespace std;

vector<unsigned char> FileIO::readFileBinary(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        handleFileError("open for reading", filename);
        return {};
    }

    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0, ios::beg);

    vector<unsigned char> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    file.close();

    return buffer;
}

bool FileIO::writeFileBinary(const string& filename, const vector<unsigned char>& data) {
    ofstream file(filename, ios::binary);
    if (!file) {
        handleFileError("open for writing", filename);
        return false;
    }

    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    file.close();
    return true;
}

string FileIO::readFileString(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        handleFileError("open for reading", filename);
        return "";
    }

    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

bool FileIO::writeFileString(const string& filename, const string& data) {
    ofstream file(filename, ios::binary);
    if (!file) {
        handleFileError("open for writing", filename);
        return false;
    }

    file.write(data.data(), data.size());
    file.close();
    return true;
}

ifstream FileIO::openInputFile(const string& filename, ios_base::openmode mode) {
    ifstream file(filename, mode);
    if (!file) {
        handleFileError("open", filename);
    }
    return file;
}

ofstream FileIO::openOutputFile(const string& filename, ios_base::openmode mode) {
    ofstream file(filename, mode);
    if (!file) {
        handleFileError("create", filename);
    }
    return file;
}

size_t FileIO::getFileSize(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) return 0;
    return file.tellg();
}

bool FileIO::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

unsigned char FileIO::readChar(ifstream& stream) {
    unsigned char ch;
    stream.read(reinterpret_cast<char*>(&ch), 1);
    return ch;
}

void FileIO::writeChar(ofstream& stream, unsigned char ch) {
    stream.write(reinterpret_cast<const char*>(&ch), 1);
}

string FileIO::getTempFileName(const string& prefix) {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(1000, 9999);

    return prefix + to_string(dis(gen)) + ".tmp";
}

bool FileIO::deleteFile(const string& filename) {
    return remove(filename.c_str()) == 0;
}

void FileIO::handleFileError(const string& operation, const string& filename) {
    cerr << "Error: Failed to " << operation << " file: " << filename << endl;
}