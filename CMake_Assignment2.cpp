// CMake_Assignment2.cpp : Defines the entry point for the application.
//

#include "CMake_Assignment2.h"

using namespace std;

int main()
{

    // Open the file for reading
    std::ifstream file("tweets_samples.txt");

    // Check if the file was opened successfully
    if (!file.is_open())
    {
        std::cerr << "Error: failed to open file" << std::endl;
        return 1;
    }

    // Count the number of lines in the file
    std::vector<char> buf;
    file.seekg(0, std::ios::end);
    buf.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&buf[0], buf.size());
    int line_count = std::count(buf.begin(), buf.end(), '\n');

    // Seek to the beginning of the file
    file.seekg(0);

    // Generate a random line number
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, line_count - 1);
    int line_number = dis(gen);

    // Go to the selected line
    for (int i = 0; i < line_number; ++i)
    {
        std::string line;
        std::getline(file, line);
    }

    // Read the line
    std::string result;
    std::regex timestamp_regex("[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}");
    while (std::getline(file, result))
    {
        if (std::regex_search(result, timestamp_regex))
        {
            std::smatch match;
            std::regex_search(result, match, timestamp_regex);
            std::string timestamp = match[0];
            if (timestamp == result.substr(result.size() - timestamp.size()))
            {
                break;
            }
        }
    }


}

