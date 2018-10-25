#include "gnome_fortress/game/Wall.h"

namespace gnome_fortress {
	namespace game {

		Wall::Wall(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique, float wallHealth)
			: model::BasicMeshNode(mesh, technique), health(wallHealth) {
		}

		void Wall::onUpdateSelf(float dt) {
			//Nothing yet for the walls
		}
	}
}