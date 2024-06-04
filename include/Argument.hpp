#pragma once
#include <string>
#include "Struct/Vec3.hpp"

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
    Vec3f asVec3f();
};
