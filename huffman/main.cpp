#include <iostream>
#include "huffmancoding.h"
#include "huffmandecoder.h"

int main(int argc, char *argv[])
{
    HuffmanCoding htree(true);
    htree.encodeToFile(std::string(argv[1]), std::string(argv[2]));

    HuffmanDecoder hdecode(true);
    hdecode.determineBytes(std::string(argv[2]) + ".dict");

    return 0;
}
