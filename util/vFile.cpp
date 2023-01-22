#include "vFile.h"
#include <fstream>
#include <ios>
#include <iostream>

void VectorFile::fileBuf_init(const char* filename)
{
    this->m_filename = filename;
    std::ifstream file;
    file.open(filename);

    std::string line;
    while (std::getline(file, line))
    {
        fileBuf.emplace_back(line);
    }

    file.close();
}

VectorFile::VectorFile(const char* filename)
{
    this->m_filename = filename;
    std::ifstream file;
    file.open(filename);

    std::string line;
    while (std::getline(file, line))
    {
        fileBuf.emplace_back(line);
    }

    file.close();
}

VectorFile::~VectorFile()
{
}

void VectorFile::appendLineToFile(std::string newWord)
{
    std::ofstream outFile;
    outFile.open(m_filename, std::ios::app);

    if (outFile.is_open())
    {
        outFile << newWord << std::endl;

        //next append to the buff
        fileBuf.emplace_back(newWord);
    }
    else {
        std::cerr << "Unable to open file";
    }


    outFile.close();
}

void VectorFile::insertAndOverWritefile(size_t pos, std::string newWord)
{
    fileBuf.insert(fileBuf.begin() + pos, newWord);
    std::ofstream outFile;
    outFile.open(m_filename, std::ios::trunc);
    for (auto const& line : fileBuf) {
        outFile << line << std::endl;
    }
    outFile.close();
}
void VectorFile::overWriteFile()
{
    std::ofstream outFile;
    outFile.open(m_filename, std::ios::trunc);
    for (auto const& line : fileBuf) {
        outFile << line << std::endl;
    }
    outFile.close();
}

string VectorFile::get(size_t npos)
{
	return string();
}
