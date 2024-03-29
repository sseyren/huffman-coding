#include "huffmanencoder.h"
#include "huffmannode.h"
#include "huffmanconstants.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <bitset>

HuffmanEncoder::HuffmanEncoder(bool debug): debugMode(debug) {
    std::fill(freqList, freqList+256, 0);
}

HuffmanEncoder::HuffmanEncoder(){
    HuffmanEncoder(false);
}

void HuffmanNodeListDebug(HuffmanNode *tree){
    HuffmanNode *iter = tree;
    while(iter != nullptr){
        std::cout << '(' << iter->byte << ' ' << iter->freq << ") ";
        iter = iter->next;
    }
    std::cout << std::endl;
}

void HuffmanEncoder::determineFreqs(std::string inputFile){
    if (debugMode)
        std::cout << "<!-- determineFreqs --!>" << std::endl;

    std::fstream fs(inputFile, std::fstream::in | std::fstream::binary);

    char byte;
    while(fs.get(byte)){
        fileSize++;
        freqList[(unsigned char)byte]++;
    }

    fs.close();

    if (debugMode){
        for(int i = 0; i < 256; i++){
            std::cout << i << " -> " << freqList[(unsigned char)i] << ' ';
        }
        std::cout << std::endl << std::endl;
    }
}

void HuffmanEncoder::bulildList(){
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

void HuffmanEncoder::buildTree()
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

void HuffmanEncoder::getBits(HuffmanNode *node, std::string bitseq){
    if(node->left == nullptr){
        bitMap[node->byte] = bitseq;
        return;
    }else
        getBits(node->left, bitseq + '0');

    if(node->right == nullptr)
        bitMap[node->byte] = bitseq;
    else
        getBits(node->right, bitseq + '1');
}

void HuffmanEncoder::determineBits(){
    if(debugMode)
        std::cout << "<!-- determineBits --!>" << std::endl;

    getBits(tree, "");

    if(debugMode){
        for(std::map<unsigned char, std::string>::iterator it = bitMap.begin();
            it != bitMap.end(); it++){
            std::cout << it->first << " -> " << it->second << std::endl;
        }
        std::cout << std::endl;
    }
}

void HuffmanEncoder::prepareDictFile(std::string dictFile){
    std::fstream dfs (dictFile, std::fstream::out);

    // Writing filesize to first 4 byte of dictFile
    dfs.write((char*)&fileSize, sizeof(fileSize));

    for (std::map<unsigned char, std::string>::iterator it = bitMap.begin();
         it != bitMap.end(); it++){
        dfs << it->first << ' ' << it->second << std::endl;
    }

    dfs.close();
}

unsigned char HuffmanEncoder::stringToByte(std::string str){
    unsigned char sum = 0;
    for(char i = 0; i < 8; i++){
        sum <<= 1;
        sum += str[i] - '0';
    }
    return sum;
}

void HuffmanEncoder::encodeToFile(std::string inputFile, std::string outputFile, std::string dictFile){
    determineFreqs(inputFile); bulildList(); buildTree(); determineBits(); prepareDictFile(dictFile);

    const int bufferSize = 4096; // 4 KB

    char *buffer = new char[bufferSize];
    std::string bitString;

    std::fstream ifs(inputFile, std::fstream::in | std::fstream::binary);
    std::fstream ofs(outputFile, std::fstream::out | std::fstream::binary);

    do {
        ifs.read(buffer, bufferSize);

        // Fill bitString with encodings
        for(int i = 0; i < ifs.gcount(); i++)
            bitString += bitMap[buffer[i]];

        // Fill bitString whit zero-bits when reach end of the input file
        if(ifs.eof() && bitString.size() % 8 != 0)
            bitString += std::string(8 - (bitString.size() % 8), '0');

        // Write to output file and delete first 8 char from bitString
        while(bitString.size() >= 8){
            ofs << stringToByte(bitString);
            bitString.erase(0, 8);
        }
    }while(!ifs.eof());

    ifs.close();
    ofs.close();
}

void HuffmanEncoder::encodeToFile(std::string inputFile, std::string outputFile)
{
    encodeToFile(inputFile, outputFile, outputFile + DEFAULT_DICT_SUFFIX);
}

void HuffmanEncoder::encodeToFile(std::string inputFile)
{
    encodeToFile(inputFile, DEFAULT_OUTPUT_FILE, DEFAULT_OUTPUT_FILE + DEFAULT_DICT_SUFFIX);
}
