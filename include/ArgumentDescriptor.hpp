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
