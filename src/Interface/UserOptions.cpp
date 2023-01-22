#include "UserOptions.h"
#include "../../util/inputSanitiser.h"


UserOptions::Options UserOptions::Main()
{
    DisplayMainOptions();
    int option = get_valid_int("Option", 1, 4);
    return getOption(option);
}

UserOptions::Options UserOptions::SecondaryOption()
{
    DisplayRWOptionsV2();
    std::string option = get_valid_string("Enter 'R' to read another tweet, 'Rp' to report tweet or 'E' to exit");
    if (option == "R") return Options::READ;
    if (option == "Rp") return Options::REPORT;
    if (option == "E") return Options::EXIT;
}

void UserOptions::DisplayRWOptions()
{
    std::cout << "Please choose one of the following options:\n";
    std::cout << "R) Read a tweet\n";
    std::cout << "W) Write a tweet\n";
}

void UserOptions::DisplayMainOptions()
{
    std::cout << "Please select an option to proceed:\n";
    std::cout << "1) Read/Write a tweet\n";
    std::cout << "2) View Statistics\n";
    std::cout << "3) Display top 10 most dangerous users\n";
    std::cout << "4) Exit\n";
}

void UserOptions::DisplayRWOptionsV2()
{
    std::cout << "What would you like to do next?:\n";
    std::cout << "R) Read another tweet\n";
    std::cout << "Rp) Report tweet\n";
    std::cout << "E) Exit\n";
}

UserOptions::Options UserOptions::getOption(int option)
{
    switch (option)
    {
    case 1:
    {
    DisplayRWOptions();
    std::string read_write = get_valid_string("Enter 'R' to read or 'W' to write a tweet");
    return read_write == "R" ? Options::READ : Options::WRITE;
    }
    case 2:
        return Options::PRINT_STATS;
    case 3:
        return Options::TOP10;
    case 4:
        return Options::EXIT;
    }
}