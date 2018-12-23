#include <iostream>
#include "huffmancoding.h"

int main(int argc, char *argv[])
{
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;

    HuffmanCoding htree(true);
    htree.encodeToFile(argv[1], argv[2]);

    return 0;
}
