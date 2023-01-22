// BadTwitter.cpp : Defines the entry point for the application.
//

#include "BadTwitter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include <cctype>
#include <filesystem>

#include "src/Interface/LoginOptions.h"
#include "src/Interface/ManagerOptions.h"
#include "src/Interface/UserOptions.h"
#include "src/FileHandler.h"

#include "util/inputSanitiser.h"


enum class STATES
{

	LOGIN_PROMPT,

	LOGIN,

	SIGN_UP_USER,
	SIGN_UP_MANAGER,

	OPTIONS_MANAGER,
	OPTIONS_USER,

	//these will be the actions of the user


	//these will be the actions of the manager
	MANAGER_RESET_MOD_CONTENT,
	MANAGER_ADD_BLOCKED_CONTENT,
	MANAGER_ADD_ANOTHER_MANAGER,
	MANAGER_SET_SAMPLE_FILE,

	EXIT

};

void Login()
{
	std::ifstream inFile{ "users.txt" };
}


class Application
{
public:
	Application(STATES& current, STATES& next) :
		current{ current }, next{ next }
	{
	}

public:
	void LoginType()
	{
		type = loginOptions.MainOptions();
		next = STATES::LOGIN;
	}

	void Login()
	{
		switch (type)
		{
			case LoginOptions::LoginType::USER: 
			{
				userOptions.Main();
				break;
			}
			case LoginOptions::LoginType::MANAGER:
			{
				auto option = managerOptions.SelectMainOption();
				if (option == ManagerOptions::Options::ADD_MANAGER)
					ManagerAddAnotherManager();
				if (option == ManagerOptions::Options::ADD_TO_BLACKLIST)
					ManagerAddBlockedContent();
				if (option == ManagerOptions::Options::RESET_BLACKLIST)
					ManagerResetModContent();
				if (option == ManagerOptions::Options::SET_FILE)
					ManagerSetSampleFile();
				if (option == ManagerOptions::Options::EXIT)
						Exit();
				break;
			}
		}

		next = STATES::LOGIN;
	}

	void ManagerResetModContent()
	{
		filehandler.updateBlackList("");
		next = STATES::OPTIONS_MANAGER;
	}

	void ManagerAddBlockedContent()
	{
		filehandler.init_Blacklist("../../../Files/blacklist.txt");
		filehandler.updateBlackList(get_valid_string("Please enter the word you wish to add to the blacklist: "));
		std::cout << "Word added to blacklist";
		next = STATES::OPTIONS_MANAGER;
	}

	void ManagerAddAnotherManager()
	{
		std::string name = loginOptions.inputName();
		int regno = loginOptions.inputregNo();
		std::stringstream line;
		line << regno << " " << name << '\n';
		std::cout << "Manager added\n";
		filehandler.appendLineToUsers(line.str());
		next = STATES::OPTIONS_MANAGER;
	}

	void ManagerSetSampleFile()
	{
		std::string name = get_valid_string("Enter the new filename: ");
		filehandler.init_MainFile(name);
		//find out what happened if it breaks when we try to rename it
		std::error_code e;
		std::filesystem::rename(sampleTweetFile, "../../../Files" + name + ".txt", e);
		std::cout << e.message() << '\n';
	}

	void Exit()
	{
		exit(0);
	}

private:
	LoginOptions loginOptions;
	UserOptions userOptions;
	ManagerOptions managerOptions;

	LoginOptions::LoginType type{};
	STATES& current;
	STATES& next;
	FileHandler filehandler{};

	std::string sampleTweetFile{ "../../../Files/example_tweets.txt"};

};

int main()
{
	STATES current{ STATES::LOGIN_PROMPT };
	STATES next{ STATES::LOGIN_PROMPT };

	Application app{ current, next };

	while (true)
	{
		switch (current)
		{
			case STATES::LOGIN_PROMPT: app.LoginType(); break;
			case STATES::LOGIN: app.Login(); break;
			case STATES::MANAGER_ADD_ANOTHER_MANAGER: app.ManagerAddAnotherManager(); break;
			case STATES::MANAGER_ADD_BLOCKED_CONTENT: app.ManagerAddBlockedContent(); break;
			case STATES::MANAGER_RESET_MOD_CONTENT: app.ManagerResetModContent(); break;
			case STATES::MANAGER_SET_SAMPLE_FILE: app.ManagerSetSampleFile(); break;
			case STATES::EXIT: app.ManagerSetSampleFile(); break;
		}
		current = next;
	}
}
