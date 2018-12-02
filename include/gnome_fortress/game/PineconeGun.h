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
        Player *player, Projectiles* vector, irrklang::ISoundEngine *soundEngine);

protected:
    const static float FIRING_VELOCITY;
    const static int FIRING_RATE;

    Projectiles* bullets;

    void onUpdateSelf(float dt) override;

    //Creating bullets 
    std::vector<Projectile*> fireBullet(glm::vec3 position) override;

};

}
}