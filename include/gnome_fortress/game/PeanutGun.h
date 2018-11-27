#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/Weapon.h"

namespace gnome_fortress {
namespace game {

class Rock;

class PeanutGun : public game::Weapon {

public:
    PeanutGun(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        Player *player, Projectiles* vector);

protected:
    const static float FIRING_VELOCITY;
    const static int FIRING_RATE;

    Projectiles* bullets;

    void onUpdateSelf(float dt) override;
    //void updateWeaponSelf(float dt, Projectiles* vector) override;

    //Creating bullets 
    std::vector<Projectile*> fireBullet(glm::vec3 position) override;

};
}
}