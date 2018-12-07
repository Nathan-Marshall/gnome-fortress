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

//Set the projectile damage and lifespan. We also set the damage radius and damage values for the AOE effect this projectile creates
const float Spore::DAMAGE = 8.5f;
const float Spore::DAMAGE_RAD = 2.5f;
const float Spore::POISON_LIFESPAN = 3.0f;
const float Spore::POISON_DAMAGE = 20.0f;

float Spore::GetDamage() {
    return DAMAGE;
}

float Spore::GetDamageRad() {
    return DAMAGE_RAD;
}

//Update method for spores
void Spore::onUpdateSelf(float dt) {
    //Update how long this spore has been alive
    lifespan += dt;

    setPosition(getPosition() + (velocity *dt));
}

}
}