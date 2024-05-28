#include "Sections/CameraSection.hpp"

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
        "read",
        "Makes a camera read a index device",
        { ArgumentDescriptor("id", ArgumentType::INT), ArgumentDescriptor("index", ArgumentType::INT)},
        [this](std::vector<Argument> args) -> bool {
            int id = args[0].asInt();
            int index = args[1].asInt();
            Camera* camera = this->engine->getCamera(id-1);
            if (!camera) failError("Wrong camera index");
            Param* p = camera->getParameter("index");
            if (!p) failError("Camera has no index parameter");
            p->setValue(index);
            return true;
        }
    ));
    addSection(CommandFactory::createCommand(
        "start",
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
        "stop",
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
}

CameraSection::~CameraSection()
{
}
