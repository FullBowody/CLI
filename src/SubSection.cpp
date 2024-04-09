#include <iostream>
#include "SubSection.hpp"

SubSection::SubSection()
    : Section()
{

}

SubSection::SubSection(std::string name, std::string help)
    : Section(name, std::string(" : ") + help)
{

}

SubSection::~SubSection()
{
    while (sections.size() > 0)
        sections.erase(sections.begin());
}

void SubSection::printHelp()
{
    std::cout << "Help for " << name << " section :" << std::endl;
    for (auto section : sections)
    {
        if (section == nullptr)
            continue;
        std::cout << "  - " << section->getName() << section->getHelp() << std::endl;
    }
}

void SubSection::addSection(Section* section)
{
    sections.push_back(section);
}

bool SubSection::call(const std::string& command)
{
    if (command.empty())
        return false; // TODO : maybe enter in this section mode (cisco like)

    CommandParts cmd = parseCommand(command);

    if (cmd.name == "help")
    {
        printHelp();
        return true;
    }

    for (auto section : sections)
    {
        if (section == nullptr)
            continue;

        if (section->getName() == cmd.name)
            return section->call(cmd.args);
    }
    return false;
}

std::string SubSection::complete(const std::string& command)
{
    if (command.empty()) return "";
    CommandParts cmd = parseCommand(command);

    for (auto section : sections)
    {
        if (section == nullptr)
            continue;

        if (section->getName()._Starts_with(cmd.name))
        {
            if (section->getName() == cmd.name)
                return section->complete(cmd.args);
            return section->getName().substr(cmd.name.size());
        }
    }

    std::string help("help");
    if (help._Starts_with(cmd.name))
        return help.substr(cmd.name.size());

    return "";
}