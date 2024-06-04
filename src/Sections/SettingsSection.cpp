#include "Sections/SettingsSection.hpp"
#include "Sections/GetSetSection.hpp"
#include "CommandFactory.hpp"

Settings SettingsSection::settings;

SettingsSection::SettingsSection(Engine* engine)
    : SubSection("settings", "Edit, load, save settings"), engine(engine)
{
    addSection(new GetSetSection(
        "ups",
        "Engine updates per second",
        ArgumentType::INT,
        []() -> std::string {
            return std::to_string(settings.updatesPerSeconds);
        },
        [](Argument arg) -> bool {
            settings.updatesPerSeconds = arg.asInt();
            return true;
        }
    ));
}

SettingsSection::~SettingsSection()
{
}
