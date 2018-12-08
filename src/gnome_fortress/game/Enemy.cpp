#include "gnome_fortress/game/Enemy.h"

namespace gnome_fortress {
namespace game {


Enemy::Enemy(const model::MeshGroup *meshGroup, renderer::BasicMeshNodeTechnique *technique)
    : model::BasicMeshGroupNode(meshGroup, technique), 
    tintAlpha(0) {

    timer = 0.0f;
}


void Enemy::onUpdateSelf(float dt) {
    //Fade away the damage effect a little 
    tintAlpha -= dt * 2;

    //If the tintAlpha is > 0, the enemy has taken damage
    if (tintAlpha < 0) {
        tintAlpha = 0;
    }

    //Set the tint accordingly for children
    for (int i = 0; i < getNumChildren(); i++) {
        dynamic_cast<model::BasicMeshNode*>(getChild(i))->setTint(glm::vec4(1, 0, 0, tintAlpha));
    }
}

//Get the bounding radius of this enemy
float Enemy::GetBoundingRadius() {
    return boundingRadius;
}

//Get the attack sound byte for this enemy
const char* Enemy::GetAttackSound() {
    return attackSoundByte;
}

//Method to allow damage to be done to this enemy
void Enemy::DoDamage(float damage) {
    health -= damage;

    //Will make the enemy red momentarily
    tintAlpha = 0.4f;
}

//Get the current health of the enemy
float Enemy::GetHealth() {
    return health;
}

//Play the attack sound for this enemy
void Enemy::PlayAttackSound() {
    glm::vec3 pos = getPosition();
    irrklang::ISound *effect = soundEngine->play3D(attackSoundByte, irrklang::vec3df(pos.x, pos.y, pos.z), GL_FALSE, GL_TRUE);
    if (effect) {
        effect->setMinDistance(1.5);
        effect->setVolume(1000.0);
        effect->setIsPaused(false);
    }
}

}
}