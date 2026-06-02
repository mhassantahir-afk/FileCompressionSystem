# File Compression System

A C++20 file compression utility featuring **6 compression algorithms** and **4 custom data structures**, built as a semester project for Data Structures & Algorithms.

## Algorithms

| Algorithm | Type | Author |
|-----------|------|--------|
| **Huffman Coding** | Entropy-based prefix coding | Hassan Tahir |
| **DEFLATE** | LZ77 + Huffman cascade | Hassan Tahir |
| **LZ77** | Sliding window dictionary | Huzaifa Rauf |
| **Arithmetic Coding** | Fractional interval encoding | Huzaifa Rauf |
| **LZW** | Dictionary-based substitution | Mubashir Ali |
| **RLE** | Run-length encoding | Mubashir Ali |

## Data Structures

| Structure | Purpose | Author |
|-----------|---------|--------|
| **MinHeapTree** | Huffman tree construction | Mubashir Ali |
| **Trie / TrieNode** | LZW compression dictionary | Mubashir Ali |
| **HashTable** | LZW decompression (chaining) | Huzaifa Rauf |
| **HuffmanNode** | Huffman tree node | Hassan Tahir |

## Project Structure

```
FileCompressionSystem/
├── CMakeLists.txt
├── frontend/
│   ├── main.cpp              # Benchmarking CLI (tests all 6 algorithms)
│   └── frontend.cpp          # Simple compress/decompress CLI
├── include/
│   ├── algorithms/           # Algorithm headers
│   ├── datastructures/       # Data structure headers
│   └── utils/
│       └── FileIO.h          # File I/O utilities
├── src/
│   ├── algorithms/           # Algorithm implementations
│   ├── datastructures/       # Data structure implementations
│   └── utils/
│       └── FileIO.cpp
├── tests/                    # Individual algorithm tests
├── resources/
│   ├── TestFiles/            # Sample test files (text + compressed)
│   └── compressed_files/     # Compressed output directory
└── docs/
```

## Build & Run

### Prerequisites
- CMake 3.31+
- C++20 compiler

### Build
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Executables
| Target | Description |
|--------|-------------|
| `FileCompressionSystem` | Benchmarking tool — compresses a file with all 6 algorithms and compares ratios/speed |
| `FileCompressionSystemSimple` | Simple CLI — compress or decompress a single file |
| `HuffmanTest`, `TestArithmetic`, `TestLZ77`, `TestRLE`, `TestDeflate`, `TestLZW` | Individual algorithm tests |

## Usage

### Benchmarking mode
```bash
./FileCompressionSystem
```
Prompts for a file path, runs all algorithms, and displays a table with compression ratios and execution times.

### Simple mode
```bash
./FileCompressionSystemSimple
```
Enter a `.txt` file to compress (choose algorithm from menu) or a compressed file to decompress.

## Features

- **Lossless compression** for all 6 algorithms
- **Correctness verification** — every compressed file is decompressed and compared to the original
- **Compression ratio & timing** benchmarks
- **RLE analysis** — pre-scan to estimate suitability for run-length encoding
- **Custom data structures** built from scratch (no STL containers for core structures)
