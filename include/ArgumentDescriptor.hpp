#pragma once
#include <string>
#include "Command.hpp"

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
    CompletionCallback completion;
    
public:
    static std::string toString(ArgumentType type);

    ArgumentDescriptor();
    ArgumentDescriptor(std::string name, ArgumentType type);
    ArgumentDescriptor(std::string name, ArgumentType type, CompletionCallback completion);
    ~ArgumentDescriptor();

    bool validate(const std::string& arg) const;
    std::string complete(const std::string& arg) const;

    std::string getName() const { return name; }
    ArgumentType getType() const { return type; }
};
