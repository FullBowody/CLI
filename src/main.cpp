#include <iostream>
#include <filesystem>
#include <signal.h>
#include <thread>
#include "EngineLoader.hpp"
#include "Sections/SettingsSection.hpp"
#include "Cli.hpp"

Cli cli;

void intHandler(int dummy);

void intHandler(int dummy) {
    cli.sigKill();
    signal(SIGINT, intHandler);
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <engine_path>" << std::endl;
        return 1;
    }

    std::cout << "Loading engine from " << argv[1] << " ..." << std::endl;
    EngineLoader loader(argv[1]);
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
