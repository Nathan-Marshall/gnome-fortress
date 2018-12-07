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
    ), 
    acceleration(1.0f) {

    threshold = 10;
}

//Damage and explosion damage, lifespan, and radius variables
const float Rocket::DAMAGE = 20.0f;
const float Rocket::DAMAGE_RAD = 4.0f;
const float Rocket::EXPLOSION_DAMAGE = 50.0f;
const float Rocket::EXPLOSION_LIFESPAN = 0.5f;

//Get the amount of damage the rocket does
float Rocket::GetDamage() {
    return DAMAGE;
}

//Get the radius for the explosion the rocket creates
float Rocket::GetDamageRad() {
    return DAMAGE_RAD;
}


//Update method for the rockets
void Rocket::onUpdateSelf(float dt) {
    lifespan += dt;

    setPosition(getPosition() + (velocity * dt * acceleration));

    if (lifespan > 1) {
        acceleration += 0.5f;
    }
    setPosition(getPosition() + (velocity * dt));
}
}
}