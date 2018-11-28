#include "gnome_fortress/game/PeanutGun.h"
#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Rock.h"
#include <iostream>

namespace gnome_fortress {
namespace game {
PeanutGun::PeanutGun(
    resource::ResourceManager &resourceManager,
    renderer::BasicMeshNodeTechnique *technique,
    Player *player, Projectiles* vector)
    : game::Weapon(
        resourceManager.getOrLoadMeshGroup(resources::models::peanut_gun),
        resourceManager.getOrLoadMeshGroup(resources::models::rock1),
        technique,
        player
    ) {
    setScale(0.2f);
    bullets = vector;
}

void PeanutGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;

    if (pressed && cooldown < 0) {
        setCooldown(0.3f);
        Projectile* p = fireBullet(getPosition());
        bullets->projectiles.push_back(p);
        bullets->appendChild(p);
    }
}

const float PeanutGun::FIRING_VELOCITY = 15.0f;

Projectile* PeanutGun::fireBullet(glm::vec3 position) {
    glm::vec3 vel = glm::normalize(glm::vec3(getGlobalTransform() * glm::vec4(0, 0, -1, 0)));
    vel.x *= FIRING_VELOCITY; 
    vel.y *= FIRING_VELOCITY; 
    vel.z *= FIRING_VELOCITY;
    Projectile *p = new Rock(bulletMeshGroup, getTechnique(),
        glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);
    return p;
}
}

}