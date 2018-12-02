#include "gnome_fortress/game/PeanutGun.h"
#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Rock.h"
#include <iostream>

namespace gnome_fortress {
namespace game {
PeanutGun::PeanutGun(
    resource::ResourceManager &resourceManager,
    renderer::BasicMeshNodeTechnique *technique,
    Player *player, Projectiles* vector, irrklang::ISoundEngine *soundEngine)
    : game::Weapon(
        resourceManager.getOrLoadMeshGroup(resources::models::peanut_gun),
        resourceManager.getOrLoadMeshGroup(resources::models::rock1),
        technique,
        player
    ) {
    this->soundEngine = soundEngine;
    fireSoundByte = resourceManager.getOrLoadAudioClip(resources::audioClips::shotgun);

    setScale(0.2f);
    bullets = vector;
}

void PeanutGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;

    if (pressed && cooldown < 0) {
        setCooldown(1.0f);
        
        std::vector<Projectile*> p = fireBullet(getPosition());

        for each (Projectile* proj in p)
        {
            bullets->projectiles.push_back(proj);
            bullets->appendChild(proj);
        }
    }
}

/*void PeanutGun::updateWeaponSelf(float delta_time, Projectiles* vector) {
    
}*/

const float PeanutGun::FIRING_VELOCITY = 45.0f;

std::vector<Projectile*> PeanutGun::fireBullet(glm::vec3 position) {
    float spreadAngle = 10.0f * glm::pi<float>() / 180.0f;
    float circleRad = tan(spreadAngle);

    float distAngle;
    float circDist;

    std::vector<Projectile*> projecs;

    for (int i = 0; i < 8; i++) {
        distAngle = rand() / (float)RAND_MAX * (glm::pi<float>() * 2);
        circDist = rand() / (float)RAND_MAX * circleRad;
        circDist *= circDist / circleRad;

        glm::vec3 dir = glm::normalize(glm::vec3(circDist * cos(distAngle), circDist * sin(distAngle), -1));
        
        glm::vec3 vel = glm::normalize(glm::vec3(getGlobalTransform() * glm::vec4(dir, 0)));

        vel *= FIRING_VELOCITY;

        Projectile *p = new Rock(bulletMeshGroup, getTechnique(),
            glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);

        projecs.push_back(p);
    }

    PlayWeaponSound();

    return projecs;
}
}

}