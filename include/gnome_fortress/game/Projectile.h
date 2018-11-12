#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshGroupNode.h"

namespace gnome_fortress {
namespace game {

class Projectile : public model::BasicMeshGroupNode {
public: 

    const static float DAMAGE;

    Projectile(
            const model::MeshGroup *meshGroup,
            renderer::BasicMeshNodeTechnique *technique,
            glm::vec3 pointOfOrigin,
            glm::vec3 velocity);

    ~Projectile();

    glm::vec3 getVelocity();

    void onUpdateSelf(float delta_time) override;

    float GetDamage();

private:
    double lifespan;
    glm::vec3 velocity;

};

}
}