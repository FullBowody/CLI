#pragma once
#include <string>

typedef struct
{
    std::string name;
    std::string args;
} CommandParts;

class Section
{
protected:
    std::string name;
    std::string help;
    
    Section();
    Section(std::string name, std::string help);
    ~Section();

    CommandParts parseCommand(const std::string& command);

public:
    virtual bool call(const std::string& command) = 0;
    virtual std::string complete(const std::string& command) = 0;

    const std::string getName();
    const std::string getHelp();
};
