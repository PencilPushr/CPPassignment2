#include "FileHandler.h"
#include <iostream>
#include <iomanip>

FileHandler::FileHandler()
{
}

FileHandler::~FileHandler()
{
}

FileHandler::FileHandler(const char* fileName, const char* blackListFileName) 
	: m_file(fileName), m_blacklist(blackListFileName) 
{
}

void FileHandler::init_Blacklist(const std::string& filename)
{
	m_blacklist = VectorBlackList(filename.c_str());
}

void FileHandler::init_MainFile(const std::string& filename)
{
	m_file = VectorFile(filename.c_str());
}


void FileHandler::ApplyBlackListFilter(std::string& line)
{
	auto blacklist = m_blacklist.getBlackListBuf();
	for (auto& i : blacklist )
	{
		i = std::regex_replace(line, std::regex(i), std::string { m_blacklist.getFilterChar()});
	}
}

void FileHandler::appendLineToUsers(const std::string& line)
{	
	std::ofstream file;
	file.open("../../../Files/users.txt", std::ios::app);

	if (file.is_open())
	{
		file << line << '\n';
	}
	else {
		std::cerr << "Unable to open file";
	}


	file.close();
}

/*
void FileHandler::writeToFileCaller()
{

}
*/

void FileHandler::appendLineToFile(std::string newWord) {
	m_file.appendLineToFile(newWord);
}

void FileHandler::insertAndOverWritefile(size_t& pos, std::string& newWord) {
	m_file.insertAndOverWritefile(pos, newWord);
}

void FileHandler::updateBlackList(std::string& newWordToBlacklist) {
	m_blacklist.updateBlackList(newWordToBlacklist);
}

std::string FileHandler::getFileLine(size_t index) {
	return m_file.get(index);
}

std::string FileHandler::getBlackListLine(size_t index) {
	return m_blacklist.get(index);
}

vector<string> FileHandler::getBlackListBuf() {
	return m_blacklist.getBlackListBuf();
}

char FileHandler::getFilterChar() {
	return m_blacklist.getFilterChar();
}

std::string padWithZeros(std::string& input){
    std::ostringstream oss;
    oss < std::setfill('0') << std::setw(5) << input;
    return oss.str();
}