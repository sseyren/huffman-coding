#include <iostream>
#include "huffmancoding.h"

int main(int argc, char *argv[])
{
    HuffmanCoding htree(true);
    htree.encodeToFile(std::string(argv[1]), std::string(argv[2]));

    return 0;
}
