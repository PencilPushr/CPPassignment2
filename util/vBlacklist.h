#ifndef VECTORBLACKLIST_H
#define VECTORBLACKLIST_H

#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;

class VectorBlackList
{
private:
    std::vector<std::string> blacklistBuf;
    char m_filterChar = 'X';
public:
    VectorBlackList();
    void blacklistBuf_init(const char* filename);
    VectorBlackList(const char* filename);
    // VectorBlackList(std::ifstream& infile);
    ~VectorBlackList();
    void updateBlackList(const std::string& newWordToBlacklist);
    char getFilterChar();
    string get(size_t index);
    vector<string> getBlackListBuf();
    std::string m_filename;
};

#endif