#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H

#include <string>
#include <map>

class HuffmanDecoder
{
    std::map<std::string, unsigned char>byteMap;
public:
    bool debugMode;
    HuffmanDecoder();
    HuffmanDecoder(bool debugMode);

    void determineBytes(std::string dictFile);
};

#endif // HUFFMANDECODER_H
