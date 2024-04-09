#pragma once
#include <conio.h>
#include <iostream>

namespace Input
{
    enum Key
    {
        KEY_UP = 72,
        KEY_DOWN = 80,
        KEY_LEFT = 75,
        KEY_RIGHT = 77,
        KEY_ENTER = 13,
        KEY_ESC = 27,
        KEY_SPACE = 32,
        KEY_BACKSPACE = 8,
        KEY_TAB = 9
    };
    enum KeyType
    {
        KEY_CTRL = 224,
        KEY_ALPHA = 0,
        KEY_SPECIAL = 1
    };
    struct KeyInfos
    {
        KeyType type;
        Key key;
    };

    static bool newKey = false;
    static KeyInfos keyInfos;

    static void update()
    {
        newKey = false;
        if (kbhit())
        {
            newKey = true;

            KeyType type = (KeyType) getch();
            if (type == KeyType::KEY_CTRL)
            {
                char key = getch();
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
