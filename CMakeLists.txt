cmake_minimum_required(VERSION 2.8)

project(huffman)
add_executable (${PROJECT_NAME}
    "test.cpp"
    "huffmanencoder.cpp"
    "huffmannode.cpp"
    "huffmandecoder.cpp"
    "huffmanconstants.h"
    )
