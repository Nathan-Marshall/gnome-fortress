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
    //Initialize references to the sound engine and sound byte to be used when firing this weapon
    this->soundEngine = soundEngine;
    fireSoundByte = resourceManager.getOrLoadAudioClip(resources::audioClips::mushroom);

    setScale(0.2f);
    bullets = vector;
}

//Set the firing velocity for this weapon
const float MushroomGun::FIRING_VELOCITY = 20.0f;

//Update method for the mushroom gun
void MushroomGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;

    //Fire if the the gun is no longer on cooldown
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

//Projectile firing from the mushroom gun
std::vector<Projectile*> MushroomGun::fireBullet(glm::vec3 position) {
    glm::vec3 vel = player->getVelocity() + glm::normalize(glm::vec3(getGlobalTransform() * glm::vec4(0, 0, -1, 0))) * FIRING_VELOCITY;

    //Create a new spore when the gun is fired
    Spore *s = new Spore(bulletMeshGroup, getTechnique(),
        glm::vec3(getGlobalTransform() * glm::vec4(0.03, 0.5, -0.25, 1)), vel);
    
    //Play the firing sound
    PlayWeaponSound();

    //Append the trail effect for the spore
    s->appendChild(bullets->CreatePoisonTrail(s));

    std::vector<Projectile*> projecs;
    projecs.push_back(s);

    return projecs;
}

}
}