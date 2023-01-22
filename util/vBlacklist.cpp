#include "vBlacklist.h"
#include <iostream>

VectorBlackList::VectorBlackList()
{
}

void VectorBlackList::blacklistBuf_init(const char* filename)
{
	this->m_filename = filename;
	std::ifstream file;
	file.open(filename);

	std::string line;
	while (std::getline(file, line))
	{
		blacklistBuf.emplace_back(line);
	}

	file.close();
}

VectorBlackList::VectorBlackList(const char* filename)
{
	this->m_filename = filename;
	std::ifstream file;
	file.open(filename);
	
	std::string line;
	while (std::getline(file, line))
	{
		blacklistBuf.emplace_back(line);
	}

	file.close();
}

VectorBlackList::~VectorBlackList()
{
}

void VectorBlackList::updateBlackList(const std::string& newWordToBlacklist)
{
	std::ofstream file;
	file.open(m_filename, std::ios::app);

	if (file.is_open())
	{
		file << newWordToBlacklist << '\n';

		//next append to the buff
		blacklistBuf.emplace_back(newWordToBlacklist);
	}
	else {
		std::cerr << "Unable to open file";
	}
	

	file.close();

}

char VectorBlackList::getFilterChar()
{
	return m_filterChar;
}

string VectorBlackList::get(size_t npos)
{
	return blacklistBuf[npos];
}

vector<string> VectorBlackList::getBlackListBuf()
{
	return blacklistBuf;
}
