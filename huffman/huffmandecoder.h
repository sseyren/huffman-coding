#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H

#include <string>
#include <map>

class HuffmanDecoder
{
    unsigned int fileSize = 0;
    std::map<std::string, unsigned char>byteMap;
    void determineBytes(std::string dictFile);
public:
    bool debugMode;
    HuffmanDecoder();
    HuffmanDecoder(bool debugMode);
    void decodeFile(std::string inputFile, std::string outputFile, std::string dictFile);
};

#endif // HUFFMANDECODER_H
