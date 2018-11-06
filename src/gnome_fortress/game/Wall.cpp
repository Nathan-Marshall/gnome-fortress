#include "gnome_fortress/game/Wall.h"

namespace gnome_fortress {
namespace game {


Wall::Wall(
        const model::Mesh *mesh,
        const model::Texture *diffuse_texture,
        renderer::BasicMeshNodeTechnique *technique,
        float wallHealth)
	: model::BasicMeshNode(mesh, diffuse_texture, technique), health(wallHealth) {
}

void Wall::onUpdateSelf(float dt) {
	//Nothing yet for the walls
}


}
}