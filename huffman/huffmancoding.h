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
    std::map<unsigned char, std::string> bitMap;
    char *file;
    HuffmanNode *tree = nullptr;
    void getBits(HuffmanNode *node, std::string bitseq);
    unsigned char stringToByte(std::string str);
public:
    bool debugMode;
    HuffmanCoding(char *file, bool debug);
    HuffmanCoding(char *file);
    void determineFreqs();
    void bulildList();
    void buildTree();
    void determineBits();
    void encodeToFile(char *outputFile);
};

#endif // HUFFMANCODING_H
