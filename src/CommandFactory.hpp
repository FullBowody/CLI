#pragma once
#include "Command.hpp"
#include "Argument.hpp"
#include "ArgumentDescriptor.hpp"

namespace CommandFactory
{
    Command* createCommand(
        const std::string& name,
        const std::string& description,
        std::vector<ArgumentDescriptor> args,
        std::function<bool(std::vector<Argument>)> callback
    )
    {
        std::string builtDesc = "";
        for (int i = 0; i < args.size(); i++)
        {
            builtDesc += " [";
            builtDesc += args[i].getName() + ":" + ArgumentDescriptor::toString(args[i].getType());
            builtDesc += "]";
        }
        builtDesc += " : ";
        builtDesc += description;

        return new Command(
            name,
            builtDesc,
            [callback, args](const std::string& input) -> bool {
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

                if (parsedArgs.size() != args.size())
                    failError("Invalid number of arguments : expected " + std::to_string(args.size()) + ", got " + std::to_string(parsedArgs.size()));

                for (int i = 0; i < args.size(); i++)
                {
                    if (!args[i].validate(parsedArgs[i]))
                        failError("Argument " + std::to_string(i+1) + " should be of type " + ArgumentDescriptor::toString(args[i].getType()) + ", got " + parsedArgs[i]);
                }

                std::vector<Argument> arguments;
                for (int i = 0; i < args.size(); i++)
                    arguments.push_back(Argument(parsedArgs[i]));

                return callback(arguments);
            }
        );
    }
};
