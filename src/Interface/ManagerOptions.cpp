#include "../../util/inputSanitiser.h"
#include "ManagerOptions.h"

ManagerOptions::Options ManagerOptions::SelectMainOption()
{
    return (ManagerOptions::Options)(GetValidOption() - 1);
}

void ManagerOptions::DisplayMenu()
{
    std::cout << "Manager options:\n";
    std::cout << "1) Clear moderation list\n";
    std::cout << "2) Add word to moderation list\n";
    std::cout << "3) Add new manager\n";
    std::cout << "4) Set sample file\n";
    std::cout << "5) Exit\n";
}

int ManagerOptions::GetValidOption()
{
    DisplayMenu();
    return get_valid_int("Option", 1, 5);
}