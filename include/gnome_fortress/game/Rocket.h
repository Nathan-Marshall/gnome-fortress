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

    Rocket(
        const model::MeshGroup *bulletMeshGroup,
        renderer::BasicMeshNodeTechnique *technique,
        glm::vec3 pointOfOrigin,
        glm::vec3 velocity);

    float GetDamage() override;
    static float GetDamageRad();

    void onUpdateSelf(float delta_time) override;

private:
    float acceleration; 
};
}
}