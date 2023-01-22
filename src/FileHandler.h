#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <string>
#include <regex>
#include <fstream>

#include "Person.h"
#include "../util/vBlacklist.h"
#include "../util/vFile.h"

class FileHandler
{
private:
	VectorBlackList m_blacklist;
	VectorFile m_file;

public:
	FileHandler();
	FileHandler(const char* fileName, const char* blackListFileName);
	~FileHandler();
	void init_Blacklist(const std::string& filename);
	void init_MainFile(const std::string& filename);

	void ApplyBlackListFilter(std::string& line);
	//void writeToFilecaller();
	void appendLineToUsers(const std::string& line);

	//this is redundant, I am aware as vFile.cpp and vBlacklist house these function
	void appendLineToFile(std::string newWord);
	void insertAndOverWritefile(size_t pos, std::string newWord);
	void updateBlackList(std::string newWordToBlacklist);
	std::string getFileLine(size_t index);
	std::string getBlackListLine(size_t index);
	vector<string> getBlackListBuf();
	char getFilterChar();
};

#endif
