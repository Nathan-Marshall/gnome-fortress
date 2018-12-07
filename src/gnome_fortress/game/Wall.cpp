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

//Set wall dimensions
void Wall::SetDimensions(float l, float h, float w) {
    length = l;
    height = h;
    width = w;
}

//Get the length of the wall
float Wall::GetLength() {
    return length;
}

//Get the height of the wall
float Wall::GetHeight() {
    return height;
}

//Get the width of the wall
float Wall::GetWidth() {
    return width;
}

//Get the current health of the wall
float Wall::GetHealth() {
    return health;
}

//Do damage to this wall
void Wall::DoDamage(float d) {
    health -= d;
}

}
}