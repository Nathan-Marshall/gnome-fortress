#include "gnome_fortress/game/Projectiles.h"

namespace gnome_fortress {
	namespace game {


		Projectiles::Projectiles() {
			//Nothing yet
		}

		void Projectiles::onDrawSelf(const glm::mat4 &parentTransform) const {
			for each (Projectile* proj in projectiles)
			{
				proj->draw(glm::mat4());
			}
		}

		void Projectiles::onUpdateSelf(float dt) {
			for each (Projectile* proj in projectiles)
			{
				proj->update(dt);
			}
		}

	}
}