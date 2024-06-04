#include "Sections/PluginSection.hpp"
#include "plugins/PluginProvider.hpp"
#include "utils.hpp"

PluginSection::PluginSection(Engine* engine)
    : SubSection("plugin", "List, manage plugins"), engine(engine)
{
    addSection(CommandFactory::createCommand(
        "list",
        "List all plugins",
        { },
        [this](std::vector<Argument> args) -> bool {
            PluginProvider& provider = this->engine->getPluginProvider();
            std::vector<PluginDescriptor> plugins = provider.getPlugins();
            listVector<PluginDescriptor>("Engine plugins", plugins);
            return true;
        }
    ));
}

PluginSection::~PluginSection()
{
}
