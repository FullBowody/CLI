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
