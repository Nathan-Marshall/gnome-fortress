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
    scale(0.7f),
    currentHealth(50){

    setScale(scale);

    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = 1.8f - 0.3f; //acceptable range of angles
    float s = 0.3f + (random * diff);
    setRotation(s*glm::pi<float>(), glm::vec3(0, 0, 1));

    // turn on environment mapping
    static_cast<model::BasicMeshNode *>(getChild(0))->setEnvMapFactor(0.2);
}

const float Acorn::MAX_HEALTH = 50;

float Acorn::getScale() {
    return scale;
}

void Acorn::vanishScale() {
    scale = 0;
}

float Acorn::getCurrentHealth() {
    return currentHealth;
}

void Acorn::takeDamage() {
    currentHealth -= 3.0f;
    setScale((currentHealth / MAX_HEALTH) * scale);
}

void Acorn::onUpdateSelf(float dt) {
        
}

}
}