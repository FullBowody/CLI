#pragma once
#include "Engine.hpp"
#include "Argument.hpp"
#include "ArgumentDescriptor.hpp"
#include "SubSection.hpp"

class GetSetSection : public SubSection
{
private:
    Engine* engine;

public:
    GetSetSection(
        Engine* engine,
        std::string name,
        std::string description,
        ArgumentType type,
        std::function<std::string()> getter,
        std::function<bool(Argument)> setter
    );
    ~GetSetSection();
};
