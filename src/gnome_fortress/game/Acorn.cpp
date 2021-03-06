#include "gnome_fortress/game/Acorn.h"
#include "gnome_fortress/game/Resources.h"
#include <iostream>

namespace gnome_fortress {
namespace game {

Acorn::Acorn(
    resource::ResourceManager &resourceManager,
    renderer::BasicMeshNodeTechnique *technique)
    : model::BasicMeshGroupNode(resourceManager.getOrLoadMeshGroup(game::resources::models::acorn),
        technique),
    //Physical properties of the acorns
    scale(0.7f),
    currentHealth(50){

    setScale(scale);

    //Random orientation of the acorn
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = 1.8f - 0.3f; //acceptable range of angles
    float s = 0.3f + (random * diff);
    setRotation(s*glm::pi<float>(), glm::vec3(0, 0, 1));

    // turn on environment mapping
    static_cast<model::BasicMeshNode *>(getChild(1))->setEnvMapFactor(0.3);
}

const float Acorn::MAX_HEALTH = 50;

float Acorn::getScale() {
    return scale;
}

void Acorn::vanishScale() {
    scale = 0;
}

//Get the current acorn health
float Acorn::getCurrentHealth() {
    return currentHealth;
}

//Take damage from outside sources
void Acorn::takeDamage(float delta_time) {
    currentHealth -= 12.0f * delta_time;
    setScale((currentHealth / MAX_HEALTH) * scale);
}

void Acorn::onUpdateSelf(float dt) {
        
}

}
}