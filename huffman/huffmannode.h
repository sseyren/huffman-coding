#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

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

#endif // HUFFMANNODE_H

