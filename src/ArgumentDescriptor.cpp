#include "ArgumentDescriptor.hpp"

std::string ArgumentDescriptor::toString(ArgumentType type)
{
    switch (type)
    {
    case ArgumentType::INT: return "int";
    case ArgumentType::FLOAT: return "float";
    case ArgumentType::BOOL: return "bool";
    case ArgumentType::STRING: return "string";
    default: return "unknown";
    }
}

ArgumentDescriptor::ArgumentDescriptor()
{
}

ArgumentDescriptor::ArgumentDescriptor(std::string name, ArgumentType type)
    : name(name), type(type), completion([](std::string) -> std::string { return ""; })
{
}

ArgumentDescriptor::ArgumentDescriptor(std::string name, ArgumentType type, CompletionCallback completion)
    : name(name), type(type), completion(completion)
{
}

ArgumentDescriptor::~ArgumentDescriptor()
{
}

bool ArgumentDescriptor::validate(const std::string& arg) const
{
    switch (type)
    {
    case ArgumentType::INT:
        try { int a = std::stoi(arg); return true; }
        catch (const std::exception& e) { return false; }
    case ArgumentType::FLOAT:
        try { float f = std::stof(arg); return true; }
        catch (const std::exception& e) { return false; }
    case ArgumentType::BOOL:
        return arg == "true" || arg == "True" || arg == "TRUE" ||
               arg == "false" || arg == "False" || arg == "FALSE";
    case ArgumentType::STRING:
        return true;
    default: return false;
    }
}

std::string ArgumentDescriptor::complete(const std::string& arg) const
{
    return completion(arg);
}
