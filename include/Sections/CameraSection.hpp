#pragma once
#include "Engine.hpp"
#include "SubSection.hpp"
#include "CommandFactory.hpp"

class CameraSection : public SubSection
{
private:
    Engine* engine;
    
public:
    CameraSection(Engine* engine);
    ~CameraSection();
};
