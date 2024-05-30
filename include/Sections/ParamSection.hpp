#pragma once
#include "Engine.hpp"
#include "Argument.hpp"
#include "ArgumentDescriptor.hpp"
#include "Section.hpp"

class ParamSection : public Section
{
private:
    Engine* engine;
    std::function<ParamManager*(int)> paramManagerGetter;
    std::vector<ArgumentDescriptor> args;

public:
    ParamSection(Engine* engine, std::string name, std::string description, std::function<ParamManager*(int)> getter);
    ~ParamSection();

    bool call(const std::string& command) override;
    std::string complete(const std::string& command) override;
};
