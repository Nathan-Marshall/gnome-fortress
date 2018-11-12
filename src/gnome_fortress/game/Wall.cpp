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
	: model::BasicMeshNode(
        resourceManager.getOrLoadMeshGroup(resources::models::cube)->meshes[0],
        technique
    ),
    health(wallHealth) {
}

void Wall::onUpdateSelf(float dt) {
	//Nothing yet for the walls
}


}
}