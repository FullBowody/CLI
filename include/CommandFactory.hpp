#pragma once
#include "Command.hpp"
#include "Argument.hpp"
#include "ArgumentDescriptor.hpp"

namespace CommandFactory
{
    std::string buildArgedDesc(
        const std::string& description,
        std::vector<ArgumentDescriptor> args
    );

    bool validateArgs(
        const std::string& input,
        const std::vector<ArgumentDescriptor>& args,
        std::vector<Argument>& arguments
    );

    Command* createCommand(
        const std::string& name,
        const std::string& description,
        std::vector<ArgumentDescriptor> args,
        std::function<bool(const std::vector<Argument>&)> callback
    );
};
