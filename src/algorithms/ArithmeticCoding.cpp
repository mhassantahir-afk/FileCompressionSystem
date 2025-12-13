//
//  main.cpp
//  ArithmeticCodng
//
//  Created by Huzaifa Rauf on 12/12/2025.
//

#include <iostream>
#include <fstream>
using namespace std;

class ArithmeticCoding {
public:
    struct Symbol {
        unsigned char ch;
        double low;
        double high;
    };

    double freq[256];
    Symbol table[256];
    int size;

    ArithmeticCoding() {
        size = 256;
        for (int i = 0; i < 256; i++) freq[i] = 1.0 / 256.0;
        buildTable();
    }

    void buildTable() {
        double cumulative = 0;
        for (int i = 0; i < size; i++) {
            table[i].ch = (unsigned char)i;
            table[i].low = cumulative;
            table[i].high = cumulative + freq[i];
            cumulative += freq[i];
        }
    }

    void calculateFrequencies(const char* filename, int &fileSize) {
        for (int i = 0; i < 256; i++) freq[i] = 0;

        ifstream fin(filename, ios::binary);
        unsigned char ch;
        fileSize = 0;

        while (fin.read((char*)&ch, 1)) {
            freq[ch]++;
            fileSize++;
        }
        fin.close();

        if (fileSize == 0) fileSize = 1;

        for (int i = 0; i < 256; i++) freq[i] /= fileSize;

        buildTable();
    }

    double encodeFile(const char* filename) {
        ifstream fin(filename, ios::binary);
        unsigned char ch;

        double low = 0, high = 1;

        while (fin.read((char*)&ch, 1)) {
            double range = high - low;
            high = low + range * table[ch].high;
            low = low + range * table[ch].low;
        }
        fin.close();

        return (low + high) / 2;
    }

    void decodeToFile(double code, int length, const char* outname) {
        ofstream fout(outname, ios::binary);

        for (int k = 0; k < length; k++) {
            for (int i = 0; i < size; i++) {
                if (code >= table[i].low && code < table[i].high) {
                    unsigned char ch = (unsigned char)i;
                    fout.write((char*)&ch, 1);

                    double l = table[i].low;
                    double h = table[i].high;

                    code = (code - l) / (h - l);
                    break;
                }
            }
        }

        fout.close();
    }

    void compress(const char* input, const char* output) {
        int length = 0;
        calculateFrequencies(input, length);

        double encodedNumber = encodeFile(input);

        ofstream fout(output, ios::binary);

        for (int i = 0; i < 256; i++)
            fout.write((char*)&freq[i], sizeof(double));

        fout.write((char*)&length, sizeof(int));
        fout.write((char*)&encodedNumber, sizeof(double));

        fout.close();
    }

    void decompress(const char* input, const char* output) {
        ifstream fin(input, ios::binary);

        for (int i = 0; i < 256; i++)
            fin.read((char*)&freq[i], sizeof(double));

        int length;
        double code;

        fin.read((char*)&length, sizeof(int));
        fin.read((char*)&code, sizeof(double));

        fin.close();

        buildTable();

        decodeToFile(code, length, output);
    }
};

int main() {
    ArithmeticCoding ac;

    const char* inputFile = "input.txt";
    const char* compressed = "compressed.bin";
  //  const char* decompressed = "output.txt";

    ac.compress(inputFile, compressed);
    cout << "File compressed to compressed.bin\n";

 //   ac.decompress(compressed, decompressed);
    cout << "File decompressed to output.txt\n";

    return 0;
}
