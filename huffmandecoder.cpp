#include "huffmandecoder.h"
#include "huffmanconstants.h"

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>

HuffmanDecoder::HuffmanDecoder(bool debugMode):debugMode(debugMode) {}
HuffmanDecoder::HuffmanDecoder():debugMode(false){}

void HuffmanDecoder::determineBytes(std::string dictFile){
    if (debugMode)
        std::cout << "<!-- determineBytes --!>" << std::endl;

    std::fstream dfs(dictFile, std::fstream::in | std::fstream::binary);

    // Reading filesize from first 4 byte of dictFile
    dfs.read((char*)&fileSize, sizeof(fileSize));

    bool lineEnded = true;
    char iter;

    unsigned char byte;
    std::string bitString;

    while (dfs.get(iter)) {
        // If line already ended, get byte
        if (lineEnded){
            byte = (unsigned char)iter;
            lineEnded = false;
        // If reached endline, put them byteMap
        }else if (iter == '\n'){
            lineEnded = true;
            byteMap[bitString] = byte;
            bitString.clear();
        // If char isn't "space" character, collect bits
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

void HuffmanDecoder::decodeFile(std::string inputFile, std::string outputFile, std::string dictFile){
    determineBytes(dictFile);

    const int bufferSize = 4096; // 4 KB

    char *buffer = new char[bufferSize];
    std::string bitString;

    std::fstream ifs(inputFile, std::fstream::in | std::fstream::binary);
    std::fstream ofs(outputFile, std::fstream::out | std::fstream::binary);
    std::string outputString;

    unsigned int encodedBytes = 0;

    do {
        ifs.read(buffer, bufferSize);

        // Change bytes to bits
        for (int i = 0; i < ifs.gcount(); i++){
            std::bitset<8> bitset(buffer[i]);
            bitString += bitset.to_string();
        }

        int stringSize = bitString.size();

        for (int i = 1; i <= stringSize; i++){
            std::map<std::string, unsigned char>::iterator iter = byteMap.find(bitString.substr(0, i));

            // If not found this bit sequence in byteMap
            if (iter != byteMap.end()){
                bitString.erase(0, i);

                // Synchronise iteration and size for truncated string
                i = 1;
                stringSize -= i;

                outputString += iter->second;
                encodedBytes++;
                if(encodedBytes == fileSize)
                    break;
            }
        }

        // Read from buffer to file and clear buffer
        ofs << outputString;
        outputString.clear();

    }while(!ifs.eof());

    ifs.close();
    ofs.close();
}

void HuffmanDecoder::decodeFile(std::string inputFile, std::string outputFile){
    decodeFile(inputFile, outputFile, outputFile + DEFAULT_DICT_SUFFIX);
}

void HuffmanDecoder::decodeFile(std::string inputFile){
    decodeFile(inputFile, DEFAULT_OUTPUT_FILE, DEFAULT_OUTPUT_FILE + DEFAULT_DICT_SUFFIX);
}
