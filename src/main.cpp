#include <iostream>
#include <filesystem>
#include <signal.h>
#include <thread>
#include "EngineLoader.hpp"
#include "Sections/SettingsSection.hpp"
#include "Cli.hpp"

#ifdef _WIN32
const std::string ENGINE_PATH = "./Engine.dll";
#else
const std::string ENGINE_PATH = "./libEngine.so";
#endif

Cli cli;

void intHandler(int dummy) {
    cli.shouldRun = false;
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    if (argc > 1) // If engine folder specified, go to that folder
        std::filesystem::current_path(std::string(argv[1]));

    std::cout << "Loading engine from " << ENGINE_PATH << "..." << std::endl;
    EngineLoader loader(ENGINE_PATH);
    Engine* engine = loader.createEngine();
    if (!engine)
    {
        std::cerr << std::endl << "Error : Failed to load engine!" << std::endl;
        return 1;
    }

    signal(SIGINT, intHandler);

    std::cout << "Starting engine ..." << std::endl;
    engine->start();

    std::cout << "Done." << std::endl;

    cli.init(engine);

    auto last = std::chrono::steady_clock::now();
    while (cli.shouldRun)
    {
        cli.update();

        auto now = std::chrono::steady_clock::now();
        auto dt_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();

        int ups = SettingsSection::settings.updatesPerSeconds;
        if (ups > 0 && dt_ms >= 1000 / ups)
        {
            int err = engine->update(dt_ms / 1000.0f);
            if (err)
            {
                std::cerr << "\nError : Engine update failed with code " << err << std::endl;
                break;
            }
            last = now;
        }

        // wait 1ms to avoid 100% CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "Stopping engine ..." << std::endl;
    engine->stop();
    loader.destroyEngine(engine);

    std::cout << "Goodbye." << std::endl;
    return 0;
}
