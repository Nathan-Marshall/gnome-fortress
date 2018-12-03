#include "gnome_fortress/game/MushroomGun.h"
#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Spore.h"
namespace gnome_fortress {
namespace game {
MushroomGun::MushroomGun(
    resource::ResourceManager &resourceManager,
    renderer::BasicMeshNodeTechnique *technique,
    Player *player, Projectiles* vector, irrklang::ISoundEngine *soundEngine)
    : game::Weapon(
        resourceManager.getOrLoadMeshGroup(resources::models::mushroom_gun),
        resourceManager.getOrLoadMeshGroup(resources::models::rock5),
        technique,
        player
    ) {
    this->soundEngine = soundEngine;
    fireSoundByte = resourceManager.getOrLoadAudioClip(resources::audioClips::mushroom);

    setScale(0.2f);
    bullets = vector;
}

const float MushroomGun::FIRING_VELOCITY = 10.0f;

void MushroomGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;

    if (pressed && cooldown < 0) {
        setCooldown(0.7f);
        std::vector<Projectile*> p = fireBullet(getPosition());

        for each (Projectile* proj in p)
        {
            bullets->projectiles.push_back(proj);
            bullets->appendChild(proj);
        }
    }
}

std::vector<Projectile*> MushroomGun::fireBullet(glm::vec3 position) {
    glm::vec3 vel = glm::normalize(glm::vec3(getGlobalTransform() * glm::vec4(0, 0, -1, 0)));
    vel.x *= FIRING_VELOCITY;
    vel.y *= FIRING_VELOCITY;
    vel.z *= FIRING_VELOCITY;
    Spore *s = new Spore(bulletMeshGroup, getTechnique(),
        glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);
    
    PlayWeaponSound();

    std::vector<Projectile*> projecs;
    projecs.push_back(s);

    return projecs;
}

}
}