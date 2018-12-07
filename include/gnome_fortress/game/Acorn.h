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

class Acorn : public model::BasicMeshGroupNode {

public:
    Acorn(resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique);

    float getScale();
    void vanishScale();

    //Get the current acorn health
    float getCurrentHealth();

    //Have the acorn take damage from outside sources
    void takeDamage(float delta_time);

    //Max health for the acorn
    const static float MAX_HEALTH;

protected: 
    float scale;
    float currentHealth;
    

    void onUpdateSelf(float dt) override;

};

}
}