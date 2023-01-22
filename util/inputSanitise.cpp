#include "inputSanitiser.h"
#include <sstream>
#include <algorithm>

bool is_valid_int(int& x, const std::string& input)
{
    std::stringstream ss(input);
    ss >> x;
    return ss.eof() && !ss.fail();
}

int get_valid_int(const std::string& message, int lower_bound, int upper_bound)
{
    std::string input;
    int result = 0;
    while (true)
    {
        std::getline(std::cin, input);
        if (is_valid_int(result, input) && (result >= lower_bound) && (result <= upper_bound))
        {
            break;
        }
        std::cout << "Invalid " << message << ", valid range = " << lower_bound << " to " << upper_bound << "\n";
    }
    return result;
}

std::string get_valid_string(const std::string& message)
{
    std::string input;
    while (true)
    {
        std::cout << message;
        std::getline(std::cin, input);
        if (!input.empty())
        {
            break;
        }
        std::cout << message << " cannot be empty\n";
    }
    return input;
}

bool is_within_range(int value, int lower, int upper)
{
    return (value >= lower) && (value <= upper);
}

bool is_valid_float(float& x, const std::string& input)
{
    try
    {
        x = std::stof(input);
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

float get_valid_float(const std::string& message, float lower_bound, float upper_bound)
{
    std::string input;
    float result = 0;
    while (true)
    {
        std::getline(std::cin, input);
        if (is_valid_float(result, input) && (result >= lower_bound) && (result <= upper_bound))
        {
            break;
        }
        std::cout << "Invalid " << message << ", valid range = " << lower_bound << " to " << upper_bound << "\n";
    }
    return result;
}

template <typename T>
void clear_input_stream(T& in) {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void press_enter_to_continue() {
    std::cout << "Press enter to continue..." << std::endl;
    clear_input_stream(std::cin);
    std::cin.get();
}

std::string to_upper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

std::string to_lower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

bool confirm_action(std::string message) {
    std::string input;
    while (true) {
        std::cout << message << " (y/n): ";
        std::getline(std::cin, input);
        input = to_lower(input);
        if (input == "y" || input == "yes") {
            return true;
        }
        else if (input == "n" || input == "no") {
            return false;
        }
    }
}