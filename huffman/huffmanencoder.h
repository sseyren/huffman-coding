#ifndef HUFFMANENCODER_H
#define HUFFMANENCODER_H

#include "huffmannode.h"
#include <map>
#include <string>

class HuffmanEncoder
{
    unsigned int fileSize = 0;
    int freqList[256];
    HuffmanNode *tree = nullptr;
    std::map<unsigned char, std::string> bitMap;

    void getBits(HuffmanNode *node, std::string bitseq);
    unsigned char stringToByte(std::string str);

    void determineFreqs(std::string inputFile);
    void bulildList();
    void buildTree();
    void determineBits();
    void prepareDictFile(std::string dictFile);
public:
    bool debugMode;

    HuffmanEncoder(bool debug);
    HuffmanEncoder();

    void encodeToFile(std::string inputFile, std::string outputFile, std::string dictFile);
    void encodeToFile(std::string inputFile, std::string outputFile);
    void encodeToFile(std::string inputFile);
};

#endif // HUFFMANENCODER_H
