#include "gnome_fortress/game/PineconeGun.h"
#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Rocket.h"

namespace gnome_fortress {
namespace game {
PineconeGun::PineconeGun(
    resource::ResourceManager &resourceManager,
    renderer::BasicMeshNodeTechnique *technique,
    Player *player, Projectiles* vector)
    : game::Weapon(
        resourceManager.getOrLoadMeshGroup(resources::models::pinecone_gun),
        resourceManager.getOrLoadMeshGroup(resources::models::berry),
        technique,
        player
    ) {
    setScale(0.2f);
    bullets = vector;
}

void PineconeGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;

    if (pressed && cooldown < 0) {
        setCooldown(1.4f);
        Projectile* p = fireBullet(getPosition());
        bullets->projectiles.push_back(p);
        bullets->appendChild(p);
    }
}

const float PineconeGun::FIRING_VELOCITY = 5.0f;

Projectile* PineconeGun::fireBullet(glm::vec3 position) {
    glm::vec3 vel = glm::normalize(glm::vec3(getGlobalTransform() * glm::vec4(0, 0, -1, 0)));
    vel.x *= FIRING_VELOCITY;
    vel.y *= FIRING_VELOCITY;
    vel.z *= FIRING_VELOCITY;
    Projectile *p = new Rocket(bulletMeshGroup, getTechnique(),
        glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);
    return p;
}

}
}