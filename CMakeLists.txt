cmake_minimum_required(VERSION 3.31)
project(FileCompressionSystem)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(CompressionAlgorithms
        src/algorithms/huffman.cpp
        src/algorithms/LZW.cpp
        src/algorithms/LZ77.cpp
        src/algorithms/RLE.cpp
        src/algorithms/Deflate.cpp
        src/algorithms/ArithmeticCoding.cpp
        src/datastructures/HuffmanNode.cpp
        src/datastructures/MinHeap.cpp
        src/datastructures/Trie.cpp
        src/datastructures/HashTable.cpp
        src/utils/FileIO.cpp
        include/utils/FileIO.h
)

add_executable(FileCompressionSystem
        frontend/main.cpp
)
target_link_libraries(FileCompressionSystem
        PRIVATE CompressionAlgorithms
)

add_executable(FileCompressionSystemSimple
        frontend/frontend.cpp
)
target_link_libraries(FileCompressionSystemSimple
        PRIVATE CompressionAlgorithms
)

add_executable(HuffmanTest
        tests/TestHuffman.cpp
        src/algorithms/huffman.cpp
        src/datastructures/HuffmanNode.cpp
        src/datastructures/MinHeap.cpp
        src/utils/FileIO.cpp
)

add_executable(TestArithmetic
        tests/TestArithmetic.cpp
        src/algorithms/ArithmeticCoding.cpp
        src/utils/FileIO.cpp
)

add_executable(TestLZ77
        tests/TestLZ77.cpp
        src/algorithms/LZ77.cpp
        src/utils/FileIO.cpp
)

add_executable(TestRLE
        tests/TestRLE.cpp
        src/algorithms/RLE.cpp
        src/utils/FileIO.cpp
)

add_executable(TestDeflate
        tests/TestDeflate.cpp
        src/algorithms/Deflate.cpp
        src/algorithms/lz77.cpp
        src/algorithms/huffman.cpp
        src/datastructures/HuffmanNode.cpp
        src/datastructures/MinHeap.cpp
        src/utils/FileIO.cpp
)

add_executable(TestLZW
        tests/TestLZW.cpp
        src/algorithms/LZW.cpp
        src/datastructures/Trie.cpp
        src/datastructures/HashTable.cpp
        src/utils/FileIO.cpp
)