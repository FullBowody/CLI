#include "Sections/PluginSection.hpp"
#include "plugins/PluginProvider.hpp"

PluginSection::PluginSection(Engine* engine)
    : SubSection("plugin", "list and manage plugins"), engine(engine)
{
    addSection(CommandFactory::createCommand(
        "list",
        "List all plugins",
        { },
        [this](std::vector<Argument> args) -> bool {
            std::cout << "Engine plugins :" << std::endl;
            PluginProvider& provider = this->engine->getPluginProvider();
            auto plugins = provider.getPlugins();
            for (auto plugin : plugins)
                std::cout << "  - " << plugin.getName() << std::endl;
            return true;
        }
    ));
}

PluginSection::~PluginSection()
{
}
