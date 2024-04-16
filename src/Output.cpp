#include "Output.hpp"
#include <iostream>

namespace Output
{
    const char* BG_RED = "\033[41m";
    const char* BG_GREEN = "\033[42m";
    const char* BG_YELLOW = "\033[43m";
    const char* BG_BLUE = "\033[44m";
    const char* BG_MAGENTA = "\033[45m";
    const char* BG_CYAN = "\033[46m";
    const char* BG_WHITE = "\033[47m";
    const char* BG_GRAY = "\033[100m";
    const char* BG_RESET = "\033[49m";

    const char* FG_RED = "\033[31m";
    const char* FG_GREEN = "\033[32m";
    const char* FG_YELLOW = "\033[33m";
    const char* FG_BLUE = "\033[34m";
    const char* FG_MAGENTA = "\033[35m";
    const char* FG_CYAN = "\033[36m";
    const char* FG_WHITE = "\033[37m";
    const char* FG_GRAY = "\033[90m";
    const char* FG_RESET = "\033[39m";

    const char* BOLD = "\033[1m";
    const char* UNDERLINE = "\033[4m";
    const char* INVERSE = "\033[7m";
    const char* RESET = "\033[0m";

    std::string Header = std::string(FG_CYAN) + BOLD + "FullBowody" + FG_WHITE + ">" + RESET + " ";

    std::string _lastCommand = "";
    std::string _lastComplete = "";

    void ClearLine()
    {
        std::cout << "\r";
        for (int i = 0; i <= _lastCommand.size() + _lastComplete.size() + Header.size(); i++)
            std::cout << " ";
    }

    void DrawLine()
    {
        std::cout << "\r" << Header <<
            _lastCommand << FG_GRAY <<
            _lastComplete << RESET <<
            "\r" << Header << _lastCommand;
    }

    void ShowCommand(const std::string& command)
    {
        _lastCommand = command;
    }

    void ShowComplete(const std::string& complete)
    {
        _lastComplete = complete;
    }
};
