#include <iostream>
#include "huffmancoding.h"

int main(int argc, char *argv[])
{
    std::cout << argv[1] << std::endl;

    HuffmanCoding htree(argv[1], true);
    htree.determineFreqs();
    htree.bulildList();
    htree.buildTree();

    return 0;
}
