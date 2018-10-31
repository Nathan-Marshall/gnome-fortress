#include "gnome_fortress/game/Enemy.h"

namespace gnome_fortress {
namespace game {


Enemy::Enemy(const model::Mesh *mesh, const model::Texture *diffuse_texture, renderer::BasicMeshNodeTechnique *technique)
	: model::BasicMeshNode(mesh, diffuse_texture, technique) {
	//Nothing yet
}


void Enemy::onUpdateSelf(float dt) {

}


}
}