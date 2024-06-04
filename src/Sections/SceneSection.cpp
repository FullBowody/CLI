#include "Sections/SceneSection.hpp"
#include "utils.hpp"

SceneSection::SceneSection(Engine* engine)
    : SubSection("scene", "Add, remove, list makers in scene"), engine(engine)
{
    addSection(CommandFactory::createCommand(
        "list",
        "List all markers in the scene",
        { },
        [this](std::vector<Argument> args) -> bool {
            Scene& scene = this->engine->getScene();
            const std::vector<Marker>& markers = scene.getMarkers();
            listVector<Marker>("Scene markers", markers);
            return true;
        }
    ));

    addSection(CommandFactory::createCommand(
        "add",
        "Add a marker to the scene",
        {
            ArgumentDescriptor("id", ArgumentType::INT),
            ArgumentDescriptor("pos", ArgumentType::VEC3),
            ArgumentDescriptor("rot", ArgumentType::VEC3),
        },
        [this](std::vector<Argument> args) -> bool {
            int id = args[0].asInt();
            Vec3f pos = args[1].asVec3f();
            Quaternion rot = Quaternion::FromEuler(args[2].asVec3f());
            Scene& scene = this->engine->getScene();
            scene.addMarker(Marker(Pose(pos, rot), id));
            return true;
        }
    ));

    addSection(CommandFactory::createCommand(
        "remove",
        "Remove a marker from the scene",
        { ArgumentDescriptor("id", ArgumentType::INT) },
        [this](std::vector<Argument> args) -> bool {
            int id = args[0].asInt();
            Scene& scene = this->engine->getScene();
            scene.removeMarker(id);
            return true;
        }
    ));
}

SceneSection::~SceneSection()
{
}
