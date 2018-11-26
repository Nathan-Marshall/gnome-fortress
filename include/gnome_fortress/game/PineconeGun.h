#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/Weapon.h"

namespace gnome_fortress {
namespace game {

class Rocket;

class PineconeGun : public game::Weapon {

public:
    PineconeGun(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        Player *player);

protected:
    const static float FIRING_VELOCITY;
    const static int FIRING_RATE;

    //void onUpdateSelf(float dt) override;
    void updateWeaponSelf(float dt, Projectiles* vector) override;

    //Creating bullets 
    Projectile* fireBullet(glm::vec3 position) override;

};

}
}