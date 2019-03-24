#include <iostream>
#include "huffmanencoder.h"
#include "huffmandecoder.h"

int main(int argc, char *argv[])
{
    HuffmanEncoder hencode(true);
    hencode.encodeToFile(std::string(argv[1]), std::string(argv[2]), std::string(argv[3]));

    HuffmanDecoder hdecode(true);
    hdecode.decodeFile(std::string(argv[2]), std::string(argv[2]) + ".orig", std::string(argv[3]));

    return 0;
}
