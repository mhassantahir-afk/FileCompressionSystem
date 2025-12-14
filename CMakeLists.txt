cmake_minimum_required(VERSION 3.31)
project(FileCompressionSystem)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(FileCompressionSystem frontend/main.cpp
        src/datastructures/HuffmanNode.cpp
        src/datastructures/BST.cpp
        src/datastructures/CircularLinkedList.cpp
        src/datastructures/hashing.cpp
        src/datastructures/LinearLinkedList.cpp
        src/datastructures/MinHeap.cpp
        src/datastructures/Queue.cpp
        src/datastructures/Stack.cpp
        src/datastructures/trie.cpp
        include/datastructures/Tree.h
        include/datastructures/BSTNode.h
        include/datastructures/CLLNode.h
        include/datastructures/CicularLinkedList.h
        include/datastructures/LLNode.h
        include/datastructures/LinkedList.h
        include/datastructures/MinHeapTree.h
        include/datastructures/HuffmanNode.h
        include/datastructures/TrieNode.h
        include/datastructures/Trie.h
        tests/TestHuffman.cpp
        include/algorithms/huffman.h
        tests/TestArithmetic.cpp
        include/algorithms/ArithmeticCoding.h
        include/algorithms/lz77.h
        include/algorithms/RLE.h
        tests/Testlz77.cpp
        tests/TestRLE.cpp)

add_executable(HuffmanTest
        tests/TestHuffman.cpp
        src/algorithms/huffman.cpp
        src/datastructures/HuffmanNode.cpp
)

add_executable(TestArithmetic
        tests/TestArithmetic.cpp
        src/algorithms/ArithmeticCoding.cpp
)

add_executable(TestLZ77
        tests/TestLZ77.cpp
        src/algorithms/LZ77.cpp
)

add_executable(TestRLE
        tests/TestRLE.cpp
        src/algorithms/RLE.cpp
)