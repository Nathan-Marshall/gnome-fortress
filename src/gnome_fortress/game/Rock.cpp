#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Rock.h"

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

    threshold = 0.5;
}

const float Rock::DAMAGE = 4.0f;

float Rock::GetDamage() {
    return DAMAGE;
}

void Rock::onUpdateSelf(float dt) {
    lifespan += dt;

    setPosition(getPosition() + (velocity * dt));

    lifespan += 1 * dt;
}
}
}