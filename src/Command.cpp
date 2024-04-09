#include "Command.hpp"

Command::Command(std::string name, std::string help, CommandCallback callback)
    : Section(name, help), callback(callback)
{

}

Command::~Command()
{

}

bool Command::call(const std::string& args)
{
    return callback(args);
}

std::string Command::complete(const std::string& command)
{
    return "";
}
