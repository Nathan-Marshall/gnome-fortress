#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/Weapon.h"

namespace gnome_fortress {
namespace game {

class Spore;

class MushroomGun : public game::Weapon {

public:
    MushroomGun(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        Player *player, Projectiles* vector);

protected:
    const static float FIRING_VELOCITY;
    const static int FIRING_RATE;

    Projectiles* bullets;

    void onUpdateSelf(float dt) override;

    //Creating bullets 
    Projectile* fireBullet(glm::vec3 position) override;
};

}
}