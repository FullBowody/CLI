#include "Keyboard.hpp"
#include <unistd.h> // read()
    
Keyboard::Keyboard()
{
#ifndef _WIN32
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
    peek_character=-1;
#endif
}
    
Keyboard::~Keyboard()
{
#ifndef _WIN32
    tcsetattr(0, TCSANOW, &initial_settings);
#endif
}
    
int Keyboard::kbhit()
{
#ifdef _WIN32
    return kbhit();
#else
    unsigned char ch;
    int nread;
    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);

    if (nread == 1){
        peek_character = ch;
        return 1;
    }
    return 0;
#endif
}
    
int Keyboard::getch()
{
#ifdef _WIN32
    return getch();
#else
    char ch;

    if (peek_character != -1){
        ch = peek_character;
        peek_character = -1;
    }
    else read(0,&ch,1);
    return ch;
#endif
}
