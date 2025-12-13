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
        include/datastructures/Trie.h)
