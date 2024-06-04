#include "ArgumentDescriptor.hpp"

std::string ArgumentDescriptor::toString(ArgumentType type)
{
    switch (type)
    {
    case ArgumentType::INT: return "int";
    case ArgumentType::FLOAT: return "float";
    case ArgumentType::BOOL: return "bool";
    case ArgumentType::STRING: return "string";
    case ArgumentType::VEC3: return "vec3";
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
    case ArgumentType::VEC3:
    {
        int pos = 0, oldPos = 0, count = 0;
        while (pos < arg.size())
        {
            if (arg[++pos] == ',' || pos == arg.size())
            {
                std::string sub = arg.substr(oldPos, pos - oldPos);
                try { float f = std::stof(sub); }
                catch (const std::exception& e) { return false; }
                oldPos = pos + 1;
                count++;
            }
        }
        return count == 3;
    }
    default: return false;
    }
}

std::string ArgumentDescriptor::complete(const std::string& arg) const
{
    return completion(arg);
}
