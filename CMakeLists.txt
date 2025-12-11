cmake_minimum_required(VERSION 3.31)
project(FileCompressionSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(FileCompressionSystem frontend/main.cpp
        include/datastructures/Tree.h
        include/datastructures/BSTNode.h
        include/datastructures/CLLNode.h
        include/datastructures/CicularLinkedList.h
        include/datastructures/LLNode.h
        include/datastructures/LinkedList.h
        include/datastructures/MinHeapTree.h
        src/datastructures/HuffmanNode.cpp
        include/datastructures/HuffmanNode.h
        include/datastructures/TrieNode.h
        include/datastructures/Trie.h)
