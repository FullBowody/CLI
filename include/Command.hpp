#pragma once
#include <functional>
#include <iostream>
#include "Section.hpp"

#define failError(msg) { std::cout << "Error : " << msg << std::endl; return false; return false; }

using CommandCallback = std::function<bool(const std::string&)>;

class Command : public Section
{
private:
    CommandCallback callback;

public:
    Command(std::string name, std::string help, CommandCallback callback);
    ~Command();

    bool call(const std::string& args);
    std::string complete(const std::string& command);
};
