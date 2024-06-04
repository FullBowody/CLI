#include "Argument.hpp"

Argument::Argument(std::string arg)
    : arg(arg)
{
}

Argument::~Argument()
{
}

int Argument::asInt()
{
    return std::stoi(arg);
}

bool Argument::asBool()
{
    if (arg == "true" || arg == "True" || arg == "TRUE")
        return true;
    return false;
}

float Argument::asFloat()
{
    return std::stof(arg);
}

std::string Argument::asString()
{
    return arg;
}

Vec3f Argument::asVec3f()
{
    int pos = 0, oldPos = 0, count = 0;
    float values[3];
    while (pos < arg.size())
    {
        if (arg[++pos] == ',' || pos == arg.size())
        {
            std::string sub = arg.substr(oldPos, pos - oldPos);
            values[count++] = std::stof(sub);
            oldPos = pos + 1;
        }
    }
    return Vec3f(values[0], values[1], values[2]);
}
