#ifndef VECTORFILE_H
#define VECTORFILE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class VectorFile
{
private:
    std::vector<std::string> fileBuf;
    size_t lineCount;
public:
    VectorFile() = default;
    void fileBuf_init(const char* filename);
    VectorFile(const char* filename);
    ~VectorFile();
    void appendLineToFile(std::string newWord);
    void insertAndOverWritefile(size_t pos, std::string newWord);
    void overWriteFile();
    string get(size_t index);
    std::string m_filename;
};

#endif