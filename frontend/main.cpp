/**
 * File Compression System - CLI Frontend
 *
 * This program compares various compression algorithms on a given text file.
 * It measures execution time, compression ratio, and displays results in a table.
 *
 * Dependencies: All compression algorithms and data structures are properly included.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <algorithm>
#include <memory>
// Include algorithm headers
#include "algorithms/huffman.h"
#include "algorithms/LZW.h"
#include "algorithms/lz77.h"
#include "algorithms/RLE.h"
#include "algorithms/deflate.h"
#include "algorithms/ArithmeticCoding.h"

// Include data structures
#include "datastructures/Trie.h"
#include "datastructures/HashTable.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

using namespace std;
namespace fs = std::filesystem;

// ============================================================================
// STRUCTURES AND DATA DEFINITIONS
// ============================================================================

/**
 * Represents a compression algorithm with its execution results
 */
struct AlgorithmResult {
    string name;
    double originalSizeKB{0.0};
    double compressedSizeKB{0.0};
    double compressionRatio{0.0};  // As percentage (smaller = better)
    long long timeMs{0};
    bool success{false};
    string errorMessage;
};

/**
 * Interface for compression algorithms
 */
class ICompressionAlgorithm {
public:
    virtual ~ICompressionAlgorithm() = default;
    virtual string getName() const = 0;
    virtual bool compress(const string& inputPath, const string& outputPath) = 0;
    virtual bool decompress(const string& inputPath, const string& outputPath) = 0;
    virtual string getOutputExtension() const = 0;
};

// ============================================================================
// ALGORITHM ADAPTERS
// ============================================================================

/**
 * Adapter for Huffman Coding
 */
class HuffmanAdapter : public ICompressionAlgorithm {
public:
    string getName() const override { return "Huffman Coding"; }
    string getOutputExtension() const override { return ".huf"; }

    bool compress(const string& inputPath, const string& outputPath) override {
        compressFile(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }

    bool decompress(const string& inputPath, const string& outputPath) override {
        decompressFile(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }
};

/**
 * Adapter for LZW Compression
 */
class LZWAdapter : public ICompressionAlgorithm {
public:
    string getName() const override { return "LZW"; }
    string getOutputExtension() const override { return ".lzw"; }

    bool compress(const string& inputPath, const string& outputPath) override {
        Trie trie;
        LZW lzw;
        lzw.compress(inputPath, outputPath, trie);
        return fs::exists(outputPath);
    }

    bool decompress(const string& inputPath, const string& outputPath) override {
        HashTable table(1024);
        LZW lzw;
        lzw.decompress(inputPath, outputPath, table);
        return fs::exists(outputPath);
    }
};

/**
 * Adapter for LZ77 Compression
 */
class LZ77Adapter : public ICompressionAlgorithm {
public:
    string getName() const override { return "LZ77"; }
    string getOutputExtension() const override { return ".lz77"; }

    bool compress(const string& inputPath, const string& outputPath) override {
        LZ77 lz77;
        lz77.compress(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }

    bool decompress(const string& inputPath, const string& outputPath) override {
        LZ77 lz77;
        lz77.decompress(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }
};

/**
 * Adapter for Run-Length Encoding
 */
class RLEAdapter : public ICompressionAlgorithm {
public:
    string getName() const override { return "Run-Length Encoding"; }
    string getOutputExtension() const override { return ".rle"; }

    bool compress(const string& inputPath, const string& outputPath) override {
        rleCompressFile(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }

    bool decompress(const string& inputPath, const string& outputPath) override {
        rleDecompressFile(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }
};

/**
 * Adapter for DEFLATE Compression
 */
class DeflateAdapter : public ICompressionAlgorithm {
public:
    string getName() const override { return "DEFLATE"; }
    string getOutputExtension() const override { return ".deflate"; }

    bool compress(const string& inputPath, const string& outputPath) override {
        Deflate deflate;
        deflate.compress(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }

    bool decompress(const string& inputPath, const string& outputPath) override {
        Deflate deflate;
        deflate.decompress(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }
};

/**
 * Adapter for Arithmetic Coding
 */
class ArithmeticCodingAdapter : public ICompressionAlgorithm {
public:
    string getName() const override { return "Arithmetic Coding"; }
    string getOutputExtension() const override { return ".arith"; }

    bool compress(const string& inputPath, const string& outputPath) override {
        ArithmeticCoding ac;
        ac.compress(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }

    bool decompress(const string& inputPath, const string& outputPath) override {
        ArithmeticCoding ac;
        ac.decompress(inputPath.c_str(), outputPath.c_str());
        return fs::exists(outputPath);
    }
};

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

/**
 * Validates the input file
 */
bool validateInputFile(const string& filePath) {
    // Check if file exists
    if (!fs::exists(filePath)) {
        cerr << "Error: File '" << filePath << "' does not exist." << endl;
        return false;
    }

    // Check if it's a regular file
    if (!fs::is_regular_file(filePath)) {
        cerr << "Error: '" << filePath << "' is not a regular file." << endl;
        return false;
    }

    // Check file extension (optional .txt requirement)
    if (filePath.length() >= 4) {
        string extension = filePath.substr(filePath.length() - 4);
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        if (extension != ".txt") {
            cout << "Warning: File '" << filePath << "' is not a .txt file." << endl;
            cout << "Continue anyway? (y/n): ";
            char response;
            cin >> response;
            cin.ignore();  // Clear newline
            if (response != 'y' && response != 'Y') {
                return false;
            }
        }
    }

    // Check if file is not empty
    ifstream file(filePath, ios::binary | ios::ate);
    streamsize fileSize = file.tellg();
    file.close();

    if (fileSize == 0) {
        cerr << "Error: File '" << filePath << "' is empty." << endl;
        return false;
    }

    if (fileSize < 0) {
        cerr << "Error: Could not read file '" << filePath << "'." << endl;
        return false;
    }

    return true;
}

/**
 * Gets file size in kilobytes
 */
double getFileSizeKB(const string& filePath) {
    try {
        uintmax_t size = fs::file_size(filePath);
        return size / 1024.0;
    } catch (const fs::filesystem_error& e) {
        cerr << "Error getting file size for '" << filePath << "': " << e.what() << endl;
        return 0.0;
    }
}

/**
 * Executes a compression algorithm and measures its performance
 */
AlgorithmResult executeAlgorithm(ICompressionAlgorithm& algorithm,
                                 const string& inputPath,
                                 const string& baseOutputPath,
                                 int testRun = 0) {
    AlgorithmResult result;
    result.name = algorithm.getName();

    try {
        // Generate output file path
        string outputPath = baseOutputPath + "_" + to_string(testRun) + algorithm.getOutputExtension();

        // Measure original file size
        double originalSize = getFileSizeKB(inputPath);
        result.originalSizeKB = originalSize;

        if (originalSize <= 0) {
            result.success = false;
            result.errorMessage = "Could not read input file size";
            return result;
        }

        // Execute compression with timing
        auto startTime = chrono::high_resolution_clock::now();
        bool success = algorithm.compress(inputPath, outputPath);
        auto endTime = chrono::high_resolution_clock::now();

        if (success && fs::exists(outputPath)) {
            // Measure compressed file size
            double compressedSize = getFileSizeKB(outputPath);
            result.compressedSizeKB = compressedSize;

            // Calculate compression ratio (as percentage of original)
            if (originalSize > 0) {
                result.compressionRatio = (compressedSize / originalSize) * 100.0;
            }

            // Calculate execution time
            result.timeMs = chrono::duration_cast<chrono::milliseconds>(
                endTime - startTime).count();

            result.success = true;

            // Optional: Verify compression by decompressing
            string decompressedPath = outputPath + ".decomp";
            if (algorithm.decompress(outputPath, decompressedPath)) {
                // Verify decompressed file matches original size
                double decompressedSize = getFileSizeKB(decompressedPath);
                if (abs(decompressedSize - originalSize) > 0.1) {
                    cerr << "Warning: " << algorithm.getName()
                         << " decompression size mismatch: expected "
                         << originalSize << " KB, got " << decompressedSize << " KB" << endl;
                }
                fs::remove(decompressedPath);
            }

            // Clean up compressed file
            fs::remove(outputPath);
        } else {
            result.success = false;
            result.errorMessage = "Compression failed or output file not created";
        }

    } catch (const exception& e) {
        result.success = false;
        result.errorMessage = string("Exception: ") + e.what();
        cerr << "Error in " << algorithm.getName() << ": " << e.what() << endl;
    } catch (...) {
        result.success = false;
        result.errorMessage = "Unknown error occurred";
        cerr << "Unknown error in " << algorithm.getName() << endl;
    }

    return result;
}

/**
 * Displays results in a formatted table
 */
void displayResultsTable(const vector<AlgorithmResult>& results) {
    // Table headers
    cout << "\n" << string(120, '=') << "\n";
    cout << "COMPRESSION ALGORITHM COMPARISON RESULTS\n";
    cout << string(120, '=') << "\n";

    // Column widths
    const int col1 = 25;  // Algorithm Name
    const int col2 = 20;  // Original Size
    const int col3 = 20;  // Compressed Size
    const int col4 = 20;  // Compression Ratio
    const int col5 = 15;  // Time Taken
    const int col6 = 20;  // Status

    // Print header
    cout << left
         << setw(col1) << "Algorithm Name"
         << setw(col2) << "Original Size (KB)"
         << setw(col3) << "Compressed Size (KB)"
         << setw(col4) << "Compression Ratio (%)"
         << setw(col5) << "Time Taken (ms)"
         << setw(col6) << "Status"
         << "\n";

    cout << string(120, '-') << "\n";

    // Print results
    for (const auto& result : results) {
        cout << left << setw(col1) << result.name;

        if (result.success) {
            cout << fixed << setprecision(2)
                 << setw(col2) << result.originalSizeKB
                 << setw(col3) << result.compressedSizeKB
                 << setw(col4) << result.compressionRatio
                 << setw(col5) << result.timeMs
                 << setw(col6) << "✓ Success";
        } else {
            cout << setw(col2) << "N/A"
                 << setw(col3) << "N/A"
                 << setw(col4) << "N/A"
                 << setw(col5) << "N/A"
                 << setw(col6) << "✗ Failed";
            if (!result.errorMessage.empty()) {
                cout << " (" << result.errorMessage << ")";
            }
        }
        cout << "\n";
    }

    cout << string(120, '=') << "\n";
}

/**
 * Performs RLE suitability analysis
 */
void performRLEAnalysis(const string& filePath) {
    cout << "\nRUN-LENGTH ENCODING (RLE) ANALYSIS:\n";
    cout << string(40, '-') << "\n";
    analyzeFileForRLE(filePath.c_str());
    cout << string(40, '-') << "\n";
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║     FILE COMPRESSION SYSTEM - COMPARISON TOOL      ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n\n";

    // Get input file path
    string inputFilePath;
    cout << "Enter the path to the input file: ";
    getline(cin, inputFilePath);

    // Remove quotes if present (common when dragging/dropping files)
    if (!inputFilePath.empty() && inputFilePath.front() == '"' && inputFilePath.back() == '"') {
        inputFilePath = inputFilePath.substr(1, inputFilePath.size() - 2);
    }

    // Validate input file
    if (!validateInputFile(inputFilePath)) {
        cerr << "\nExiting due to input file validation failure.\n";
        return 1;
    }

    // Get original file size
    double originalSizeKB = getFileSizeKB(inputFilePath);
    cout << "\n📄 Input File: " << fs::path(inputFilePath).filename().string() << "\n";
    cout << "📊 Original Size: " << fixed << setprecision(2)
         << originalSizeKB << " KB (" << (originalSizeKB * 1024) << " bytes)\n";

    // Perform RLE analysis
    performRLEAnalysis(inputFilePath);

    // Initialize compression algorithms
    vector<unique_ptr<ICompressionAlgorithm>> algorithms;
    algorithms.push_back(make_unique<HuffmanAdapter>());
    algorithms.push_back(make_unique<LZ77Adapter>());
    algorithms.push_back(make_unique<RLEAdapter>());
    algorithms.push_back(make_unique<LZWAdapter>());
    algorithms.push_back(make_unique<DeflateAdapter>());
    algorithms.push_back(make_unique<ArithmeticCodingAdapter>());

    cout << "\n⚡ Executing " << algorithms.size() << " compression algorithms...\n";
    cout << "   This may take a moment depending on file size...\n\n";

    // Generate base output path (without extension)
    string timestamp = to_string(chrono::system_clock::now().time_since_epoch().count());
    string baseOutputPath = "temp_compressed_" + timestamp;

    vector<AlgorithmResult> results;
    int algorithmNumber = 1;

    // Execute all algorithms
    for (auto& algorithm : algorithms) {
        cout << "   [" << algorithmNumber << "/" << algorithms.size() << "] "
             << algorithm->getName() << "... ";
        cout.flush();

        AlgorithmResult result = executeAlgorithm(*algorithm, inputFilePath, baseOutputPath, algorithmNumber);
        results.push_back(result);

        if (result.success) {
            cout << "✓ Done (" << result.timeMs << " ms, "
                 << fixed << setprecision(2) << result.compressionRatio << "%)\n";
        } else {
            cout << "✗ Failed\n";
        }

        algorithmNumber++;
    }

    // Display results
    displayResultsTable(results);

    // Clean up any remaining temporary files
    cout << "\n🧹 Cleaning up temporary files...\n";
    try {
        for (int i = 1; i <= algorithms.size(); i++) {
            for (auto& algo : algorithms) {
                string pattern = baseOutputPath + "_" + to_string(i) + algo->getOutputExtension();
                if (fs::exists(pattern)) {
                    fs::remove(pattern);
                }
                string decompPattern = pattern + ".decomp";
                if (fs::exists(decompPattern)) {
                    fs::remove(decompPattern);
                }
            }
        }
        cout << "   Temporary files cleaned successfully.\n";
    } catch (const exception& e) {
        cout << "   Note: Some temporary files could not be cleaned: " << e.what() << "\n";
    }

    cout << "\n🎯 Analysis complete!\n";
    cout << "   You can now choose the best algorithm for your needs.\n";
    cout << "════════════════════════════════════════════════════════════\n";
}