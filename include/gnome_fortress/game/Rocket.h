#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/Projectile.h"

namespace gnome_fortress {
namespace game {

class Rocket : public game::Projectile {

public:
    const static float DAMAGE;
    const static float DAMAGE_RAD;
    const static float EXPLOSION_LIFESPAN;
    const static float EXPLOSION_DAMAGE;

    const static float ACCELERATION;

    Rocket(
        const model::MeshGroup *bulletMeshGroup,
        renderer::BasicMeshNodeTechnique *technique,
        glm::vec3 pointOfOrigin,
        glm::vec3 velocity,
        glm::vec3 accelerationDir);

    //Get the damage of a rocket
    float GetDamage() override;

    //Get the damage radius for a rocket explosion
    static float GetDamageRad();

    void onUpdateSelf(float delta_time) override;

private:
    glm::vec3 accelerationDir;
};
}
}