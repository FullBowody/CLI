#pragma once
#include <string>

namespace Output
{
    extern const char* BG_RED;
    extern const char* BG_GREEN;
    extern const char* BG_YELLOW;
    extern const char* BG_BLUE;
    extern const char* BG_MAGENTA;
    extern const char* BG_CYAN;
    extern const char* BG_WHITE;
    extern const char* BG_GRAY;
    extern const char* BG_RESET;

    extern const char* FG_RED;
    extern const char* FG_GREEN;
    extern const char* FG_YELLOW;
    extern const char* FG_BLUE;
    extern const char* FG_MAGENTA;
    extern const char* FG_CYAN;
    extern const char* FG_WHITE;
    extern const char* FG_GRAY;
    extern const char* FG_RESET;

    extern const char* BOLD;
    extern const char* UNDERLINE;
    extern const char* INVERSE;
    extern const char* RESET;

    extern std::string Header;

    extern std::string _lastCommand;
    extern std::string _lastComplete;

    void ClearLine();
    void DrawLine();
    void ShowCommand(const std::string& command);
    void ShowComplete(const std::string& complete);
};
