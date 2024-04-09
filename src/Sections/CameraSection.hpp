#pragma once
#include "SubSection.hpp"
#include "CommandFactory.hpp"

class CameraSection : public SubSection
{
private:
    Engine* engine;
    
public:
    CameraSection(Engine* engine);
    ~CameraSection();
};

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
        { },
        [this](std::vector<Argument> args) -> bool {
            this->engine->createCamera();
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
        "readwebcam",
        "Read a given webcam stream",
        { ArgumentDescriptor("id", ArgumentType::INT), ArgumentDescriptor("index", ArgumentType::INT) },
        [this](std::vector<Argument> args) -> bool {
            int id = args[0].asInt();
            int index = args[1].asInt();
            Camera* cam = this->engine->getCamera(id-1);
            if (!cam) failError("Wrong camera index");
            cam->readDevice(index);
            return true;
        }
    ));
    addSection(CommandFactory::createCommand(
        "readstream",
        "Read a given web stream",
        { ArgumentDescriptor("id", ArgumentType::INT), ArgumentDescriptor("url", ArgumentType::STRING) },
        [this](std::vector<Argument> args) -> bool {
            int id = args[0].asInt();
            std::string url = args[1].asString();
            Camera* cam = this->engine->getCamera(id-1);
            if (!cam) failError("Wrong camera index");
            cam->readStream(url);
            return true;
        }
    ));
}

CameraSection::~CameraSection()
{
}
