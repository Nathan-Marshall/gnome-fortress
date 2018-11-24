#include "gnome_fortress/game/PeanutGun.h"
#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Rock.h"
#include <iostream>

namespace gnome_fortress {
namespace game {
PeanutGun::PeanutGun(
    resource::ResourceManager &resourceManager,
    renderer::BasicMeshNodeTechnique *technique,
    Player *player)
    : game::Weapon(
        resourceManager.getOrLoadMeshGroup(resources::models::peanut_gun),
        resourceManager.getOrLoadMeshGroup(resources::models::rock1),
        technique,
        player
    ) {

}

void PeanutGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;
}

Projectile* PeanutGun::fireBullet(glm::vec3 position) {
    glm::vec3 vel = glm::normalize(glm::vec3(getGlobalTransform() * glm::vec4(0, 0, -1, 0)));
    vel.x *= 5.0; //FIRING_VELOCITY;
    vel.y *= 5.0; //FIRING_VELOCITY;
    vel.z *= 5.0; //FIRING_VELOCITY;
    std::cout << "IN PEANUTGUN.CPP" << std::endl;
    Projectile *p = new Rock(bulletMeshGroup, getTechnique(),
        glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);
   // Projectile *p = new Projectile(bulletMeshGroup, getTechnique(),
   //     glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);
    return p;
}
}

}