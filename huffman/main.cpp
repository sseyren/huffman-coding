#include <iostream>
#include "huffmancoding.h"

int main(int argc, char *argv[])
{
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;

    HuffmanCoding htree(argv[1], true);
    htree.determineFreqs();
    htree.bulildList();
    htree.buildTree();
    htree.determineBits();
    htree.encodeToFile(argv[2]);

    return 0;
}
