#include "LoginOptions.h"
#include <cctype>
#include "../../util/inputSanitiser.h"

LoginOptions::LoginType LoginOptions::MainOptions()
{
    DisplayLoginOption();
    std::string option = get_valid_string("Enter 'U' for User or 'M' for Manager\n");
    return (option == "U") ? LoginType::USER : LoginType::MANAGER;
}

void LoginOptions::DisplayLoginOption()
{
    std::cout << "Please select your role: \n";
    std::cout << "U) User\n";
    std::cout << "M) Manager\n";
}

std::string LoginOptions::getLoginOptions()
{
    std::string input;
    std::cout << "Enter 'U' for User or 'M' for Manager: ";
    std::getline(std::cin, input);
    while (input != "U" && input != "M") {
        std::cout << "Invalid input, please enter 'U' for User or 'M' for Manager: ";
        std::getline(std::cin, input);
    }
    return input;
}


std::string LoginOptions::inputName()
{
	return this->Login_firstname = get_valid_string("Enter first name: ");
}

int LoginOptions::inputregNo()
{
	return this->Login_regNo = get_valid_int("Enter registration number: ", 10000000, 99999999);
}

int LoginOptions::inputManagerregNo()
{
    return this->Login_regNo = get_valid_int("Enter registration number: ", 0, 9999);
}
