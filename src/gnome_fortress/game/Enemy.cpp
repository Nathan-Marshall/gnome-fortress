#include "gnome_fortress/game/Enemy.h"

namespace gnome_fortress {
namespace game {


Enemy::Enemy(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique)
	: model::BasicMeshNode(mesh, technique) {
	//Nothing yet
}


void Enemy::onUpdateSelf(float dt) {

}


}
}