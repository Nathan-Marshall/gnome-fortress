#include "gnome_fortress/game/PineconeGun.h"
#include "gnome_fortress/game/Resources.h"
#include "gnome_fortress/game/Rocket.h"

namespace gnome_fortress {
namespace game {
PineconeGun::PineconeGun(
    resource::ResourceManager &resourceManager,
    renderer::BasicMeshNodeTechnique *technique,
    Player *player, Projectiles* vector, irrklang::ISoundEngine *soundEngine)
    : game::Weapon(
        resourceManager.getOrLoadMeshGroup(resources::models::pinecone_gun),
        resourceManager.getOrLoadMeshGroup(resources::models::berry),
        technique,
        player
    ) {
    //References to the main sound engine and the pinecone gun sound effect
    this->soundEngine = soundEngine;
    fireSoundByte = resourceManager.getOrLoadAudioClip(resources::audioClips::rocket);

    setScale(0.2f);
    bullets = vector;
}

//Pinecone gun update method
void PineconeGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;

    //Fire projectiles if the weapon is not on cooldown
    if (pressed && cooldown < 0) {
        setCooldown(1.4f);
        
        std::vector<Projectile*> p = fireBullet(getPosition());

        for each (Projectile* proj in p)
        {
            bullets->projectiles.push_back(proj);
            bullets->appendChild(proj);
        }
    }
}

//Set the firing velocity for the pinecone gun
const float PineconeGun::FIRING_VELOCITY = 5.0f;

//Fire a rocket from the pinecone gun
std::vector<Projectile*> PineconeGun::fireBullet(glm::vec3 position) {
    glm::vec3 vel = glm::normalize(glm::vec3(getGlobalTransform() * glm::vec4(0, 0, -1, 0)));
    vel *= FIRING_VELOCITY;

    //Create a new rocket
    Rocket *p = new Rocket(bulletMeshGroup, getTechnique(),
        glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);
    
    std::vector<Projectile*> projecs;

    p->appendChild(bullets->CreateRocketTrail(p));

    //Play the rocket sound effect
    PlayWeaponSound();

    projecs.push_back(p);

    return projecs;
}

}
}