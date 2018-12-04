#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Spore.h"

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

    threshold = 10;
}

const float Spore::DAMAGE = 8.5f;
const float Spore::DAMAGE_RAD = 2.0f;

float Spore::GetDamage() {
    return DAMAGE;
}

float Spore::GetDamageRad() {
    return DAMAGE_RAD;
}

void Spore::onUpdateSelf(float dt) {
    lifespan += dt;

    setPosition(getPosition() + (velocity *dt));
    lifespan += 1 * dt;
}

}
}