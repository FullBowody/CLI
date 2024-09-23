#pragma once
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif
    
class Keyboard
{
private:
#ifndef _WIN32
    struct termios initial_settings, new_settings;
    int peek_character;
#endif

public:
    Keyboard();
    ~Keyboard();

    int kbhit();
    int getch();
};
