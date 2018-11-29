#include "gnome_fortress/game/Wall.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {

Wall::Wall(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        float wallHealth)
    : model::BasicMeshGroupNode(
        resourceManager.getOrLoadMeshGroup(resources::models::fence),
        technique
    ),
    health(wallHealth) {
}

void Wall::onUpdateSelf(float dt) {
    //Nothing yet for the walls
}

void Wall::SetDimensions(float l, float h, float w) {
    length = l;
    height = h;
    width = w;
}
float Wall::GetLength() {
    return length;
}

float Wall::GetHeight() {
    return height;
}

float Wall::GetWidth() {
    return width;
}

float Wall::GetHealth() {
    return health;
}

void Wall::DoDamage(float d) {
    health -= d;
}

}
}