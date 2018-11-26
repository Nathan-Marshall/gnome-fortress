#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Rocket.h"

namespace gnome_fortress {
namespace game {
Rocket::Rocket(
    const model::MeshGroup *bulletMeshGroup,
    renderer::BasicMeshNodeTechnique *technique,
    glm::vec3 pointOfOrigin,
    glm::vec3 velocity) : game::Projectile(
        bulletMeshGroup,
        technique,
        pointOfOrigin,
        velocity
    ) {

}

void Rocket::onUpdateSelf(float dt) {
    setPosition(getPosition() + (velocity * dt));
    lifespan += 1 * dt;
}
}
}