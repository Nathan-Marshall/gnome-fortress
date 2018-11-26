#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Spore.h"
#include <iostream>

namespace gnome_fortress {
namespace game {

Spore::Spore(
    const model::MeshGroup *bulletMeshGroup,
    renderer::BasicMeshNodeTechnique *technique,
    glm::vec3 pointOfOrigin,
    glm::vec3 velocity) : game::Projectile(
        bulletMeshGroup,
        technique,
        pointOfOrigin,
        velocity
    ) {
    std::cout << "IN SPORE.CPP" << std::endl;
}

void Spore::onUpdateSelf(float dt) {
    setPosition(getPosition() + (velocity *dt));
    lifespan += 1 * dt;
}

}
}