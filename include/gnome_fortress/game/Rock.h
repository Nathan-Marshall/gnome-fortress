#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/Projectile.h"


namespace gnome_fortress {
namespace game {

class Rock : public game::Projectile {

public: 
    Rock(
        const model::MeshGroup *bulletMeshGroup,
        renderer::BasicMeshNodeTechnique *technique,
        glm::vec3 pointOfOrigin,
        glm::vec3 velocity);

    //Get the damage that a rock should do
    float GetDamage() override;

    void onUpdateSelf(float delta_time) override;

private:
    //Damage value for a rock projectile
    const static float DAMAGE;
};
}
}