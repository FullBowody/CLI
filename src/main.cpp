#include <iostream>
#include <filesystem>
#include <signal.h>
#include <thread>
#include "EngineLoader.hpp"

const std::string ENGINE_PATH = "Engine.dll";
bool running = false;
int clock_micro = 1000000 / 60;

void intHandler(int dummy) {
    running = false;
}

int main(int argc, char const *argv[])
{
    if (argc > 1) // If engine folder specified, go to that folder
        std::filesystem::current_path(std::string(argv[1]));

    std::cout << "Loading engine at " << std::filesystem::current_path() << " ...";
    EngineLoader loader(ENGINE_PATH);
    Engine* engine = loader.createEngine();
    if (engine == nullptr)
    {
        std::cerr << std::endl << "Error : Failed to load engine!" << std::endl;
        return 1;
    }
    std::cout << " Done!" << std::endl;

    signal(SIGINT, intHandler);

    std::cout << "Starting engine ...";
    engine->start();
    std::cout << " Done!" << std::endl;

    running = true;
    auto last = std::chrono::steady_clock::now();
    while (running)
    {
        auto now = std::chrono::steady_clock::now();
        auto dt_micro = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();

        if (dt_micro < clock_micro)
        {
            if (clock_micro > 1000000 / 65) // if not too fast, sleep a bit to save CPU
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            continue;
        }

        engine->update(dt_micro / 1000000.0f);
        last = now;
    }

    std::cout << "Stopping engine ...";
    engine->stop();
    std::cout << " Done!" << std::endl;

    std::cout << "Goodbye." << std::endl;
    loader.destroyEngine(engine);

    return 0;
}
