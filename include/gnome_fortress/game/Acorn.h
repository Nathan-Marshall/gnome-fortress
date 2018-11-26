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

    //Whether or not the acorn is being eaten at the moment 

    float getScale();
    void vanishScale();

    float getCurrentHealth();
    void takeDamage();

protected: 
    float scale;
    float currentHealth;
    float maxHealth;

    void onUpdateSelf(float dt) override;

};

}
}