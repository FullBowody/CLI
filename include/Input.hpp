#pragma once
#include <iostream>
#include "Keyboard.hpp"

namespace Input
{
    enum Key
    {
#ifdef _WIN32
        KEY_UP = 72,
        KEY_DOWN = 80,
        KEY_LEFT = 75,
        KEY_RIGHT = 77,
        KEY_ENTER = 13,
        KEY_ESC = 27,
        KEY_SPACE = 32,
        KEY_BACKSPACE = 8,
        KEY_TAB = 9
#else
        KEY_UP = 65,
        KEY_DOWN = 66,
        KEY_LEFT = 68,
        KEY_RIGHT = 67,
        KEY_ENTER = 10,
        KEY_ESC = 27,
        KEY_SPACE = 32,
        KEY_BACKSPACE = 127,
        KEY_TAB = 9
#endif
    };
    enum KeyType
    {
#ifdef _WIN32
        KEY_CTRL = 224,
        KEY_ALPHA = 0,
        KEY_SPECIAL = 1
#else
        KEY_CTRL = 17,
        KEY_ALPHA = 0,
        KEY_SPECIAL = 1
#endif
    };
    struct KeyInfos
    {
        KeyType type;
        Key key;
    };

    inline static bool newKey = false;
    inline static KeyInfos keyInfos;
    inline static Keyboard keyboard;

    static void update()
    {
        newKey = false;
        if (keyboard.kbhit())
        {
            newKey = true;

            KeyType type = (KeyType) keyboard.getch();
            if (type == KeyType::KEY_CTRL)
            {
                char key = keyboard.getch();
                keyInfos = { KeyType::KEY_CTRL, (Key) key };
            }
            else
            {
                if (type >= 'a' && type <= 'z' || type >= 'A' && type <= 'Z' || type >= '0' && type <= '9')
                    keyInfos = { KeyType::KEY_ALPHA, (Key) type };
                else
                    keyInfos = { KeyType::KEY_SPECIAL, (Key) type };
            }
        }
    }
};
