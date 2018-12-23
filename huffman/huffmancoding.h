#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include <map>
#include <string>

class HuffmanNode
{
public:
    unsigned char byte = 0;
    int freq = 0;
    HuffmanNode *left = nullptr;
    HuffmanNode *right = nullptr;
    HuffmanNode *next = nullptr;
    HuffmanNode(unsigned char byte, int freq);
    HuffmanNode(unsigned char byte, int freq, HuffmanNode *left, HuffmanNode* right);
    HuffmanNode();
};

class HuffmanCoding
{
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

    HuffmanCoding(bool debug);
    HuffmanCoding();

    void encodeToFile(std::string inputFile, std::string outputFile, std::string dictFile);
    void encodeToFile(std::string inputFile, std::string outputFile);
    void encodeToFile(std::string inputFile);
};

#endif // HUFFMANCODING_H
