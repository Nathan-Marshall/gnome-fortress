#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Rocket.h"

namespace gnome_fortress {
namespace game {
Rocket::Rocket(
    const model::MeshGroup *bulletMeshGroup,
    renderer::BasicMeshNodeTechnique *technique,
    glm::vec3 pointOfOrigin,
    glm::vec3 velocity,
    glm::vec3 accelerationDir) : game::Projectile(
        bulletMeshGroup,
        technique,
        pointOfOrigin,
        velocity*0.3f
    ), 
    accelerationDir(accelerationDir) {


    //Get the axis we should rotate around
    glm::vec3 axis = glm::cross(glm::vec3(0, 0, -1), accelerationDir); //axis to rotate around 

    //Get the angle we should rotate around this axis
    float angle = acos((glm::dot(accelerationDir, glm::vec3(0, 0, -1))) / glm::length(accelerationDir));

    //Rotate around the axis
    setRotation(angle, glm::normalize(axis));

    //Rotate by 90 degrees so the cylinder is 'facing forward'
    rotate(90 * (glm::pi<float>() / 180.0f), glm::vec3(1.0, 0.0, 0.0));

    threshold = 10;
}

//Damage and explosion damage, lifespan, and radius variables
const float Rocket::DAMAGE = 300.0f;
const float Rocket::DAMAGE_RAD = 7.0f;
const float Rocket::EXPLOSION_DAMAGE = 200.0f;
const float Rocket::EXPLOSION_LIFESPAN = 0.8f;

const float Rocket::ACCELERATION = 8.0f;

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

    velocity += accelerationDir * ACCELERATION * dt;
    setPosition(getPosition() + (velocity * dt));
}
}
}