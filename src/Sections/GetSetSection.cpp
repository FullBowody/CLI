#include "Sections/GetSetSection.hpp"
#include "CommandFactory.hpp"

GetSetSection::GetSetSection(
    Engine* engine,
    std::string name,
    std::string description,
    ArgumentType type,
    std::function<std::string()> getter,
    std::function<bool(Argument)> setter
)
    : SubSection(name, std::string("Get or set ") + description), engine(engine)
{
    addSection(CommandFactory::createCommand(
        "get",
        "Get the value",
        { },
        [getter](std::vector<Argument> args) -> bool {
            std::cout << getter() << std::endl;
            return true;
        }
    ));
    addSection(CommandFactory::createCommand(
        "set",
        "Set the value",
        { ArgumentDescriptor("value", type) },
        [setter](std::vector<Argument> args) -> bool {
            return setter(args[0]);
        }
    ));
}