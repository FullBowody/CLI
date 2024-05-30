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

ParamSection::ParamSection(Engine* engine, std::string name, std::string description, std::function<ParamManager*(int)> getter)
    : Section(name, ""), engine(engine), paramManagerGetter(getter)
{
    args.push_back(ArgumentDescriptor("id", ArgumentType::INT));
    this->help = CommandFactory::buildArgedDesc(description, this->args);
    // auto params = paramManager->getParameters();
    // for (auto& param : params)
    // {
    //     addSection(new GetSetSection(
    //         this->engine,
    //         param->getName(),
    //         param->getName(),
    //         paramType2argType(param->getType()),
    //         [param]() -> std::string {
    //             return param->asString();
    //         },
    //         [param](Argument arg) -> bool {
    //             param->setValue(arg.asString());
    //             return true;
    //         }
    //     ));
    // }
}

ParamSection::~ParamSection()
{
    
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
        std::cout << "Available parameters:" << std::endl;
        for (Param* param : params)
        {
            // TODO : Display type too
            std::cout << "  - " << param->getName() << std::endl;
        }
        return true;
    }
    
    Param* param;
    for (Param* p : params)
    {
        if (p->getName() == paramCommand.name)
        {
            param = p;
            break;
        }
    }
    if (param == nullptr)
    {
        failError("Invalid parameter name");
    }

    Section* s = new GetSetSection(
        param->getName(),
        param->getName(),
        paramType2argType(param->getType()),
        [param]() -> std::string {
            return param->asString();
        },
        [param](Argument arg) -> bool {
            param->setValue(arg.asInt());
            return true;
        }
    );

    // TODO : change from getsetsection to own section
    // to write camera params [id] set/get property value
    // instead of camera params [id] property set/get value

    // TODO : Fix autocompletion

    return s->call(paramCommand.args);
}

std::string ParamSection::complete(const std::string& command)
{
    return "";
}
