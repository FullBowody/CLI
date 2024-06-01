#include "Command.hpp"

Command::Command(std::string name, std::string help, CommandCallback callback)
    : Section(name, help), callback(callback), completion([](std::string) -> std::string { return ""; })
{

}

Command::Command(std::string name, std::string help, CommandCallback callback, CompletionCallback completion)
    : Section(name, help), callback(callback), completion(completion)
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
    return completion(command);
}
