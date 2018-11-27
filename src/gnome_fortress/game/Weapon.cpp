#include "gnome_fortress/game/Weapon.h"
#include <iostream>

//These should be set based on the kind of gun created 
int FIRING_RATE = 5;
double FIRING_VELOCITY = 5.0;

namespace gnome_fortress {
namespace game {

Weapon::Weapon(
        const model::MeshGroup *gunMeshGroup,
        const model::MeshGroup *bMeshGroup,
        renderer::BasicMeshNodeTechnique *technique,
        Player *player)
    : model::BasicMeshGroupNode(gunMeshGroup, technique),
      pressed(false), 
      bulletMeshGroup(bMeshGroup) {
    setPosition(0.8, 0, 0);
}

Weapon::~Weapon() { 
}

bool Weapon::isPressed() {
    return pressed;
}

void Weapon::setPressed(bool isPressed) {
    pressed = isPressed;
}

float Weapon::getCooldown() {
    return cooldown;
}

void Weapon::setCooldown(float cd) {
    cooldown = cd;
}

std::vector<Projectile*> Weapon::fireBullet(glm::vec3 position) {
    glm::vec3 vel = glm::normalize(glm::vec3(getGlobalTransform() * glm::vec4(0, 0, -1, 0)));
    vel.x *= 5.0; //FIRING_VELOCITY;
    vel.y *= 5.0; //FIRING_VELOCITY;
    vel.z *= 5.0; //FIRING_VELOCITY;
    Projectile *p = new Projectile(bulletMeshGroup, getTechnique(),
        glm::vec3(getGlobalTransform() * glm::vec4(0.03,0.5,-0.25,1)), vel);

    std::vector<Projectile*> projecs;
    projecs.push_back(p);

    return projecs;
}

void Weapon::onUpdateSelf(float delta_time) {
    /*cooldown -= delta_time;

    if (pressed && cooldown < 0) {
        std::cout << "Shootin'" << std::endl;
    }

    // DEBUG stuff
    std::cout << "WEAPON POSITION-- x: " << getPosition().x
        << ", y: " << getPosition().y
        << ", z: " << getPosition().z
        << std::endl;*/

/*    std::cout << "VELOCITY-- x: " << velocity.x
        << ", y: " << velocity.y
        << ", z: " << velocity.z
        << std::endl;*/
}

/*void Weapon::updateWeaponSelf(float delta_time, Projectiles* vector) {

}*/


}
}