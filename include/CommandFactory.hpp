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
    );
};
