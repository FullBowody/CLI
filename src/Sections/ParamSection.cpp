#include "Sections/ParamSection.hpp"
#include "Sections/GetSetSection.hpp"
#include "CommandFactory.hpp"

ArgumentType paramType2argType(ParamType type)
{
    switch (type)
    {
        case ParamType::BOOL: return ArgumentType::BOOL;
        case ParamType::INT: return ArgumentType::INT;
        case ParamType::FLOAT: return ArgumentType::FLOAT;
        case ParamType::STRING: return ArgumentType::STRING;
        default: return ArgumentType::STRING;
    }
}

void setParamValue(Param* param, Argument value)
{
    switch (param->getType())
    {
        case ParamType::BOOL:
            param->setValue(value.asBool());
            break;
        case ParamType::INT:
            param->setValue(value.asInt());
            break;
        case ParamType::FLOAT:
            param->setValue(value.asFloat());
            break;
        case ParamType::STRING:
            param->setValue(value.asString());
            break;
    }
}

ParamSection::ParamSection(Engine* engine, std::string name, std::string description, std::function<ParamManager*(int)> getter)
    : Section(name, ""), engine(engine), paramManagerGetter(getter)
{
    args.push_back(ArgumentDescriptor("id", ArgumentType::INT));
    this->help = CommandFactory::buildArgedDesc(description, this->args);
}

ParamSection::~ParamSection()
{
    
}

void ParamSection::printHelp(const std::vector<Param*>& params)
{
    std::cout << "Available parameters:" << std::endl;
    for (Param* param : params)
    {
        std::cout << "  - " << param->getName() << " (" <<
        ArgumentDescriptor::toString(paramType2argType(param->getType())) <<
        ")" << std::endl;
    }
}

bool ParamSection::call(const std::string& command)
{
    if (command.empty())
        return false; // TODO : maybe enter in this section mode (cisco like)
        
    std::vector<Argument> arguments;
    bool valid = CommandFactory::validateArgs(command, this->args, arguments);
    if (!valid) return false;
    int index = arguments[0].asInt();

    std::string paramString = parseCommand(command).args;
    if (paramString.empty())
        return false;

    CommandParts paramCommand = parseCommand(paramString);

    ParamManager* paramManager = paramManagerGetter(index);
    if (paramManager == nullptr)
        failError("Invalid id");
    
    const std::vector<Param*>& params = paramManager->getParameters();

    if (paramCommand.name == "help")
    {
        printHelp(params);
        return true;
    }

    if (paramCommand.name != "get" && paramCommand.name != "set")
        failError("Invalid command name");

    if (paramCommand.args.empty())
        failError("Missing parameter name");

    CommandParts paramCommandArgs = parseCommand(paramCommand.args);
    
    Param* param = paramManager->getParameter(paramCommandArgs.name);
    if (param == nullptr)
        failError("Invalid parameter name");

    if (paramCommand.name == "get")
    {
        std::cout << param->asString() << std::endl;
        return true;
    }
    if (paramCommand.name == "set")
    {
        if (paramCommandArgs.args.empty())
            failError("Missing value");

        ArgumentDescriptor arg("", paramType2argType(param->getType()));
        bool valid = arg.validate(paramCommandArgs.args);
        if (!valid) failError("Invalid value");

        setParamValue(param, Argument(paramCommandArgs.args));
        return true;
    }

    return false;
}

std::string ParamSection::complete(const std::string& command)
{
    if (command.empty())
        return "";

    int nbParts = 0;
    std::string lastPart;
    for (char c : command)
    {
        if (c == ' ')
        {
            nbParts++;
            lastPart.clear();
        }
        else lastPart += c;
    }

    if (lastPart.empty())
        return "";

    switch (nbParts)
    {
        case 1: // get/set
            if (std::string("get")._Starts_with(lastPart))
                return std::string("get").substr(lastPart.size());
            if (std::string("set")._Starts_with(lastPart))
                return std::string("set").substr(lastPart.size());
            return "";
        case 2: // param name
        {
            std::string index = parseCommand(command).name;
            if (index.empty())
                return "";
            int i = -1;
            try { i = std::stoi(index); }
            catch(const std::exception& e) { return ""; }
        
            ParamManager* paramManager = paramManagerGetter(i);
            if (paramManager == nullptr)
                return "";

            const std::vector<Param*>& params = paramManager->getParameters();
            for (Param* param : params)
            {
                if (param->getName()._Starts_with(lastPart))
                    return param->getName().substr(lastPart.size());
            }
        }
    }

    return "";
}
