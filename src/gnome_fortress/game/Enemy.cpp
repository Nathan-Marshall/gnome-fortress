#include "gnome_fortress/game/Enemy.h"

namespace gnome_fortress {
namespace game {


Enemy::Enemy(const model::MeshGroup *meshGroup, renderer::BasicMeshNodeTechnique *technique)
    : model::BasicMeshGroupNode(meshGroup, technique) {

    timer = 0.0f;
}


void Enemy::onUpdateSelf(float dt) {

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