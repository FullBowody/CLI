#pragma once
#include <string>

enum class ArgumentType
{
    INT,
    FLOAT,
    BOOL,
    STRING
};

class ArgumentDescriptor
{
private:
    std::string name;
    ArgumentType type;
    
public:
    static std::string toString(ArgumentType type);

    ArgumentDescriptor();
    ArgumentDescriptor(std::string name, ArgumentType type);
    ~ArgumentDescriptor();

    bool validate(const std::string& arg) const;

    std::string getName() const { return name; }
    ArgumentType getType() const { return type; }
};

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
    : name(name), type(type)
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