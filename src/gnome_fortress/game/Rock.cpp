#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Rock.h"
#include <iostream>

namespace gnome_fortress {
namespace game {
Rock::Rock(
    const model::MeshGroup *bulletMeshGroup,
    renderer::BasicMeshNodeTechnique *technique,
    glm::vec3 pointOfOrigin,
    glm::vec3 velocity) : game::Projectile(
        bulletMeshGroup,
        technique,
        pointOfOrigin,
        velocity
    ) {
    std::cout << "IN ROCK.CPP" << std::endl;
}

void Rock::onUpdateSelf(float dt) {

    setPosition(getPosition() + (velocity * dt));

}
//resourceManager
//renderer
    //POI
    //velocity 

    //renderer::BasicMeshNodeTechnique *technique,
    //glm::vec3 pointOfOrigin,
    //glm::vec3 velocity)
    //: game::Projectile(
    //)
}
}