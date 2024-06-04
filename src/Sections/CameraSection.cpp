#include "Sections/CameraSection.hpp"
#include "Sections/ParamSection.hpp"
#include "utils.hpp"

CameraSection::CameraSection(Engine* engine)
    : SubSection("camera", "List, create, edit, delete cameras"), engine(engine)
{
    addSection(CommandFactory::createCommand(
        "list",
        "List all cameras",
        { },
        [this](std::vector<Argument> args) -> bool {
            std::vector<Camera*> cameras = this->engine->getCameras();
            listVector<Camera>("Engine cameras", cameras);
            return true;
        }
    ));
    addSection(CommandFactory::createCommand(
        "create",
        "Create a camera",
        {
            ArgumentDescriptor(
                "plugin", ArgumentType::STRING,
                [this](std::string cmd) -> std::string {
                    PluginProvider& provider = this->engine->getPluginProvider();
                    std::vector<PluginDescriptor> plugins = provider.getPlugins(PluginType::CAMERA);

                    if (std::string("help")._Starts_with(cmd))
                        return std::string("help").substr(cmd.size());

                    for (PluginDescriptor plugin : plugins)
                    {
                        std::string name = plugin.getName();
                        if (name._Starts_with(cmd))
                            return name.substr(cmd.size());
                    }
                    return "";
                }
            )
        },
        [this](std::vector<Argument> args) -> bool {
            std::string plugin = args[0].asString();

            if (plugin == "help")
            {
                PluginProvider& provider = this->engine->getPluginProvider();
                std::vector<PluginDescriptor> plugins = provider.getPlugins(PluginType::CAMERA);
                listVector<PluginDescriptor>("Available plugins", plugins);
                return true;
            }

            this->engine->createCamera(plugin);
            return true;
        }
    ));
    addSection(CommandFactory::createCommand(
        "delete",
        "Delete a camera",
        { ArgumentDescriptor("id", ArgumentType::INT) },
        [this](std::vector<Argument> args) -> bool {
            int id = args[0].asInt();
            if (!this->engine->destroyCamera(id-1))
                failError("Wrong camera index");
            return true;
        }
    ));
    addSection(CommandFactory::createCommand(
        "startTracking",
        "Starts a camera tracking",
        { ArgumentDescriptor("id", ArgumentType::INT) },
        [this](std::vector<Argument> args) -> bool {
            int id = args[0].asInt();
            Camera* camera = this->engine->getCamera(id-1);
            if (!camera) failError("Wrong camera index");
            camera->startTracking();
            return true;
        }
    ));
    addSection(CommandFactory::createCommand(
        "stopTracking",
        "Stops a camera tracking",
        { ArgumentDescriptor("id", ArgumentType::INT) },
        [this](std::vector<Argument> args) -> bool {
            int id = args[0].asInt();
            Camera* camera = this->engine->getCamera(id-1);
            if (!camera) failError("Wrong camera index");
            camera->stopTracking();
            return true;
        }
    ));
    addSection(new ParamSection(
        this->engine,
        "params",
        "edit camera parameters",
        [this](int id) -> ParamManager* {
            return this->engine->getCamera(id-1);
        }
    ));
}

CameraSection::~CameraSection()
{
}
