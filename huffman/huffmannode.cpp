#include "huffmannode.h"

HuffmanNode::HuffmanNode(unsigned char byte, int freq):
    byte(byte), freq(freq) {}

HuffmanNode::HuffmanNode(unsigned char byte, int freq, HuffmanNode *left, HuffmanNode *right):
    byte(byte), freq(freq), left(left), right(right) {}

HuffmanNode::HuffmanNode() {}
