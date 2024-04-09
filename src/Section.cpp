#include "Section.hpp"

Section::Section()
{

}

Section::Section(std::string name, std::string help)
    : name(name), help(help)
{

}

Section::~Section()
{

}

CommandParts Section::parseCommand(const std::string& command)
{
    int separator = command.find_first_of(' ');
    if (separator < 0) return { command, "" };
    return {
        command.substr(0, separator),
        command.substr(separator + 1)
    };
}

const std::string Section::getName()
{
    return name;
}

const std::string Section::getHelp()
{
    return help;
}
