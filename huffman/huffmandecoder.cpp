#include "huffmandecoder.h"
#include <iostream>
#include <fstream>
#include <string>

HuffmanDecoder::HuffmanDecoder(bool debugMode):debugMode(debugMode) {}
HuffmanDecoder::HuffmanDecoder():debugMode(false){}

void HuffmanDecoder::determineBytes(std::string dictFile){
    if (debugMode)
        std::cout << "<!-- determineBytes --!>" << std::endl;

    std::fstream dfs(dictFile, std::fstream::in | std::fstream::binary);

    bool lineEnded = true;
    char iter;

    unsigned char byte;
    std::string bitString;

    while (dfs.get(iter)) {
        if (lineEnded){
            byte = (unsigned char)iter;
            lineEnded = false;
        }else if (iter == '\n'){
            lineEnded = true;
            byteMap[bitString] = byte;
            bitString.clear();
        }else if (iter != ' '){
            bitString += iter;
        }
    }

    dfs.close();

    if(debugMode){
        for(std::map<std::string, unsigned char>::iterator it = byteMap.begin();
            it != byteMap.end(); it++){
            std::cout << it->first << " -> " << it->second << std::endl;
        }
        std::cout << std::endl;
    }
}
