#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshGroupNode.h"
#include "gnome_fortress/resource/ResourceManager.h"

namespace gnome_fortress {
namespace game {

class Projectile : public model::BasicMeshGroupNode {
public: 

    //Damage value for this projectile
    const static float DAMAGE;

    Projectile(
            const model::MeshGroup *meshGroup,
            renderer::BasicMeshNodeTechnique *technique,
            glm::vec3 pointOfOrigin,
            glm::vec3 velocity);

    ~Projectile();

    //Get the velocity of the projectils
    glm::vec3 getVelocity();

    //Update method
    void onUpdateSelf(float delta_time) override;

    //Get the damage, lifespan, and threshold values for the projectile
    virtual float GetDamage();
    double GetLifespan();
    double GetDeathThreshold();


protected:
    //Lifespance, threshold, and velocity values
    double lifespan;
    double threshold;
    glm::vec3 velocity;

};

}
}