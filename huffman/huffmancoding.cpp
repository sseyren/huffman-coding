#include "huffmancoding.h"
#include <fstream>
#include <iostream>
#include <algorithm>

HuffmanNode::HuffmanNode(unsigned char byte, int freq):
    byte(byte), freq(freq) {}

HuffmanNode::HuffmanNode(unsigned char byte, int freq, HuffmanNode *left, HuffmanNode *right):
    byte(byte), freq(freq), left(left), right(right) {}

HuffmanNode::HuffmanNode() {}

HuffmanCoding::HuffmanCoding(char *file, bool debug):
    file(file), debugMode(debug) {
    std::fill(freqList, freqList+256, 0);
}

HuffmanCoding::HuffmanCoding(char *file){
    HuffmanCoding(file, false);
}

void HuffmanNodeListDebug(HuffmanNode *tree){
    HuffmanNode *iter = tree;
    while(iter != nullptr){
        std::cout << '(' << iter->byte << ' ' << iter->freq << ") ";
        iter = iter->next;
    }
    std::cout << std::endl;
}

void HuffmanCoding::determineFreqs(){
    if (debugMode)
        std::cout << "<!-- determineFreqs --!>" << std::endl;

    std::fstream fs(file, std::fstream::in | std::fstream::binary);

    char byte;
    while(fs.get(byte))
        freqList[(unsigned char)byte]++;

    fs.close();

    if (debugMode){
        for(int i = 0; i < 256; i++){
            std::cout << i << " -> " << freqList[(unsigned char)i] << ' ';
        }
        std::cout << std::endl << std::endl;
    }
}

void HuffmanCoding::bulildList(){
    if(debugMode)
        std::cout << "<!-- buildList --!>" << std::endl;

    int min = 0;

    // Creating a empty node which will be deleted later.
    tree = new HuffmanNode;
    HuffmanNode *tail = tree;

    while(true){
        int prevMin = min;

        // Get a integer in array which bigger than current min
        for(int i = 0; i < 256; i++){
            if(freqList[i] > min){
                min = freqList[i];
                break;
            }
        }

        // If doesn't change min value, then break the loop
        if(prevMin == min)
            break;

        // Search lower value than current min
        for (int i = 0; i < 256; i++){
            if(freqList[i] < min && freqList[i] != 0)
                min = freqList[i];
        }

        // Put all min values to tree
        for (int i = 0; i < 256; i++){
            if(freqList[i] == min){
                tail->next = new HuffmanNode((unsigned char)i, freqList[i]);
                tail = tail->next;
                freqList[i] = 0;
            }
        }
    }

    // Delete first empty node
    tail = tree->next;
    delete tree;
    tree = tail;

    if(debugMode){
        HuffmanNodeListDebug(tree);
        std::cout << std::endl;
    }
}

void HuffmanCoding::buildTree()
{
    if(debugMode){
        std::cout << "<!-- buildTree --!>" << std::endl;
        HuffmanNodeListDebug(tree);
    }

    while (tree->next != nullptr){
        // Creating a new parent node which points first two node on current list
        HuffmanNode *parentNode = new HuffmanNode(0, tree->freq + tree->next->freq, tree, tree->next);

        // If list ends after these two nodes...
        if (tree->next->next != nullptr)
            tree = tree->next->next;
        else{
            tree = parentNode;
            break;
        }

        // If right position is first node on list...
        if (tree->freq >= parentNode->freq){
            parentNode->next = tree;
            tree = parentNode;
        }else{
            HuffmanNode *iter = tree;

            // Find right position for parentNode
            while (iter->next != nullptr && iter->next->freq < parentNode->freq) {
                iter = iter->next;
            }

            parentNode->next = iter->next;
            iter->next = parentNode;
        }

        if (debugMode){
            HuffmanNodeListDebug(tree);
        }
    }

    if (debugMode){
        HuffmanNodeListDebug(tree);
        std::cout << std::endl;
    }
}
