// BadTwitter.cpp : Defines the entry point for the application.
//

#include "BadTwitter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>

int main()
{
	std::ifstream file;
	file.open("users.txt");
	assert(file);
	std::string temp;
	while (std::getline(file, temp))
	{
		std::cout << temp << std::endl;
		
	}
	return 0;
}
