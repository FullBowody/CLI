#pragma once
#include "Engine.hpp"
#include "SubSection.hpp"
#include "CommandFactory.hpp"

class PluginSection : public SubSection
{
private:
    Engine* engine;
    
public:
    PluginSection(Engine* engine);
    ~PluginSection();
};
