#ifndef USEROPTIONS_H
#define USEROPTIONS_H

#include <string>

class UserOptions
{
public:
    enum class Options { READ, WRITE, REPORT, PRINT_STATS, TOP10, EXIT };

    Options Main();
    Options SecondaryOption();

private:
    void DisplayRWOptions();
    void DisplayMainOptions();
    void DisplayRWOptionsV2();

    Options getOption(int option);
};

#endif // !1