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
}

const float Spore::DAMAGE = 8.5f;

float Spore::GetDamage() {
    return DAMAGE;
}

void Spore::onUpdateSelf(float dt) {
    lifespan += dt;

    setPosition(getPosition() + (velocity *dt));
}

}
}