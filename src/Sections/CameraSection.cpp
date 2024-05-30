#include "Sections/CameraSection.hpp"
#include "Sections/ParamSection.hpp"

CameraSection::CameraSection(Engine* engine)
    : SubSection("camera", "list, create, edit, delete cameras"), engine(engine)
{
    addSection(CommandFactory::createCommand(
        "list",
        "List all cameras",
        { },
        [this](std::vector<Argument> args) -> bool {
            std::cout << "Engine cameras :" << std::endl;
            std::vector<Camera*> cameras = this->engine->getCameras();
            if (cameras.empty()) std::cout << "  - No camera" << std::endl;
            for (int i = 0; i < cameras.size(); i++)
                std::cout << "  - (" << (i+1) << ") : Camera" << std::endl;
            return true;
        }
    ));
    addSection(CommandFactory::createCommand(
        "create",
        "Create a camera",
        {
            ArgumentDescriptor("plugin", ArgumentType::STRING)
        },
        [this](std::vector<Argument> args) -> bool {
            std::string plugin = args[0].asString();
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
