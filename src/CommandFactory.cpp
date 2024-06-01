#include "CommandFactory.hpp"
#include "Output.hpp"

namespace CommandFactory
{
    std::string buildArgedDesc(
        const std::string& description,
        std::vector<ArgumentDescriptor> args
    )
    {
        std::string builtDesc = "";
        for (int i = 0; i < args.size(); i++)
        {
            builtDesc += Output::FG_GRAY;
            builtDesc += " [";
            builtDesc += Output::FG_RESET;
            builtDesc += args[i].getName() + ":";
            builtDesc += Output::FG_YELLOW;
            builtDesc += ArgumentDescriptor::toString(args[i].getType());
            builtDesc += Output::FG_GRAY;
            builtDesc += "]";
            builtDesc += Output::FG_RESET;
        }
        builtDesc += " : ";
        builtDesc += description;
        return builtDesc;
    }

    bool validateArgs(
        const std::string& input,
        const std::vector<ArgumentDescriptor>& args,
        std::vector<Argument>& arguments
    )
    {
        std::vector<std::string> parsedArgs;
        std::string arg;
        for (char c : input)
        {
            if (c == ' ')
            {
                parsedArgs.push_back(arg);
                arg.clear();
            }
            else arg += c;
        }
        if (!arg.empty()) parsedArgs.push_back(arg);

        if (parsedArgs.size() < args.size())
            failError("Invalid number of arguments : expected " + std::to_string(args.size()) + ", got " + std::to_string(parsedArgs.size()));

        for (int i = 0; i < args.size(); i++)
        {
            if (!args[i].validate(parsedArgs[i]))
                failError("Argument [" + args[i].getName() + "] should be of type " + ArgumentDescriptor::toString(args[i].getType()) + ", got " + parsedArgs[i]);
        }

        for (int i = 0; i < args.size(); i++)
            arguments.push_back(Argument(parsedArgs[i]));

        return true;
    }

    Command* createCommand(
        const std::string& name,
        const std::string& description,
        std::vector<ArgumentDescriptor> args,
        std::function<bool(const std::vector<Argument>&)> callback
    )
    {
        return new Command(
            name,
            buildArgedDesc(description, args),
            [callback, args](const std::string& input) -> bool {
                std::vector<Argument> arguments;
                bool valid = validateArgs(input, args, arguments);
                if (!valid) return false;

                return callback(arguments);
            },
            [args](const std::string& input) -> std::string {
                int nbParts = 0;
                std::string lastPart;
                for (char c : input)
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
                if (nbParts >= args.size())
                    return "";
                
                return args[nbParts].complete(lastPart);
            }
        );
    }
};
