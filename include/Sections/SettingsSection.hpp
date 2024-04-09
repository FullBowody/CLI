#pragma once
#include "SubSection.hpp"
#include "Settings.hpp"
#include "Engine.hpp"

class SettingsSection : public SubSection
{
private:
    Engine* engine;
    
public:
    static Settings settings;

    SettingsSection(Engine* engine);
    ~SettingsSection();
};
