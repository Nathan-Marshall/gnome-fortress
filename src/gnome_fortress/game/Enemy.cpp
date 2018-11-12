#include "gnome_fortress/game/Enemy.h"

namespace gnome_fortress {
namespace game {


Enemy::Enemy(const model::MeshGroup *meshGroup, renderer::BasicMeshNodeTechnique *technique)
    : model::BasicMeshGroupNode(meshGroup, technique) {
    //Nothing yet
}


void Enemy::onUpdateSelf(float dt) {

}

float Enemy::GetBoundingRadius() {
    return boundingRadius;
}

void Enemy::DoDamage(float damage) {
    health -= damage;
}

float Enemy::GetHealth() {
    return health;
}


}
}