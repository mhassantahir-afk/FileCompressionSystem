#include <iostream>
#include "algorithms/ArithmeticCoding.h"

using namespace std;

int main() {
    cout << "=== Arithmetic Coding Test ===" << endl << endl;

    ArithmeticCoding ac;

    // Test compression
    cout << "Compressing file..." << endl;
    ac.compress("../resources/TestFiles/uncompressed/uncompressed_2.txt", "../resources/TestFiles/compressed/CompressedOutofArithmetic.arc");
    cout << "File compressed successfully!" << endl << endl;

    // Test decompression
    cout << "Decompressing file..." << endl;
    ac.decompress("../resources/TestFiles/compressed/CompressedOutofArithmetic.arc", "../resources/TestFiles/uncompressed/UncompressedOutofArithmetic.txt");
    cout << "File decompressed successfully!" << endl << endl;

    cout << "Done! Check restored.txt to verify it matches the original." << endl;

    return 0;
}