#include "gnome_fortress/game/Projectile.h"

#include <iostream>

namespace gnome_fortress {
namespace game {

Projectile::Projectile(
        const model::MeshGroup *meshGroup,
        renderer::BasicMeshNodeTechnique *technique, 
        glm::vec3 pointOfOrigin,
        glm::vec3 velocity)
    : model::BasicMeshGroupNode(
        meshGroup,
        technique
      ),
      velocity(velocity), 
      lifespan(0) {

    setPosition(pointOfOrigin);

    //Make the bullets nice and smol
    setScale(0.2f);

    //Get the axis we should rotate around
    glm::vec3 axis = glm::cross(glm::vec3(0, 0, -1), velocity); //axis to rotate around 

    //Get the angle we should rotate around this axis
    float angle = acos((glm::dot(velocity, glm::vec3(0, 0, -1))) / glm::length(velocity));
        
    //Rotate around the axis
    rotate(angle, glm::normalize(axis));

    //Rotate by 90 degrees so the cylinder is 'facing forward'
    rotate(90 * (glm::pi<float>() / 180.0f), glm::vec3(1.0, 0.0, 0.0));
}

    //Set the projectile damage
    const float Projectile::DAMAGE = 10;

Projectile::~Projectile() {
    
}

//Get the velocity of the projectile
glm::vec3 Projectile::getVelocity(){
    return velocity;
}

//Get the current lifespan of the projectile (how long has it been alive)
double Projectile::GetLifespan() {
    return lifespan;
}

//Get the threshold value for the projectile (how long it CAN be alive before dying)
double Projectile::GetDeathThreshold() {
    return threshold;
}

//Get the amount of damage this projectile should do
float Projectile::GetDamage() {
    return DAMAGE;
}

//Update method for projectiles
void Projectile::onUpdateSelf(float dt) {
    setPosition(getPosition() + (velocity * dt));
}

}
}