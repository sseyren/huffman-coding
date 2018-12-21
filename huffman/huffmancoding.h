#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include <list>
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
    char *file;
    HuffmanNode *tree = nullptr;
public:
    bool debugMode;
    HuffmanCoding(char *file, bool debug);
    HuffmanCoding(char *file);
    void determineFreqs();
    void bulildList();
};

#endif // HUFFMANCODING_H
