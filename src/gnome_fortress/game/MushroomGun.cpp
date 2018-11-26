#include "gnome_fortress/game/MushroomGun.h"
#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Spore.h"

namespace gnome_fortress {
namespace game {
MushroomGun::MushroomGun(
    resource::ResourceManager &resourceManager,
    renderer::BasicMeshNodeTechnique *technique,
    Player *player)
    : game::Weapon(
        resourceManager.getOrLoadMeshGroup(resources::models::mushroom_gun),
        resourceManager.getOrLoadMeshGroup(resources::models::rock5),
        technique,
        player
    ) {

}

const float MushroomGun::FIRING_VELOCITY = 10.0f;
  
void MushroomGun::updateWeaponSelf(float delta_time, Projectiles* vector) {
    cooldown -= delta_time;

    if (pressed && cooldown < 0) {
        setCooldown(0.7f);
        Projectile* p = fireBullet(getPosition());
        vector->projectiles.push_back(p);
        vector->appendChild(p);
    }
}

Projectile* MushroomGun::fireBullet(glm::vec3 position) {
    glm::vec3 vel = glm::normalize(glm::vec3(getGlobalTransform() * glm::vec4(0, 0, -1, 0)));
    vel.x *= FIRING_VELOCITY;
    vel.y *= FIRING_VELOCITY;
    vel.z *= FIRING_VELOCITY;
    Projectile *p = new Spore(bulletMeshGroup, getTechnique(),
        glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);
    // Projectile *p = new Projectile(bulletMeshGroup, getTechnique(),
    //     glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);
    return p;
}

}
}