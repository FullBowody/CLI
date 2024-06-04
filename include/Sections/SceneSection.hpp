#pragma once
#include "Engine.hpp"
#include "SubSection.hpp"
#include "CommandFactory.hpp"

class SceneSection : public SubSection
{
private:
    Engine* engine;
    
public:
    SceneSection(Engine* engine);
    ~SceneSection();
};
