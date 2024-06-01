#pragma once
#include "SubSection.hpp"
#include "Input.hpp"
#include "Engine.hpp"

#define HISTORY_SIZE 10

class Cli: public SubSection
{
private:
    std::string command;
    std::string commands[HISTORY_SIZE];
    int commandIndex = 0;
    Engine* engine;

    void handleKeyPress(Input::KeyInfos key);
    void updateView();

public:
    bool shouldRun = true;

    Cli();
    ~Cli();

    void init(Engine* engine);
    void update();
    void sigKill();
};
