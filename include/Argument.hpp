#pragma once
#include <string>

class Argument
{
private:
    std::string arg;

public:
    Argument(std::string arg);
    ~Argument();

    int asInt();
    bool asBool();
    float asFloat();
    std::string asString();
};
