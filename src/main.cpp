#include <iostream>
#include <windows.h>
#include "Engine/EngineLoader.hpp"

const std::string ENGINE_PATH = "./Engine.dll";

int main(int argc, char const *argv[])
{
    EngineLoader loader(ENGINE_PATH);
    Engine* engine = loader.createEngine();

    engine->Run();

    loader.destroyEngine(engine);
}
