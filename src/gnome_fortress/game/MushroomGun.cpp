#include "gnome_fortress/game/MushroomGun.h"
#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {
MushroomGun::MushroomGun(
	resource::ResourceManager &resourceManager,
	renderer::BasicMeshNodeTechnique *technique,
	Player *player)
	: game::Weapon(
		resourceManager.getOrLoadMesh(resources::models::mushroom_gun),
		resourceManager.getOrLoadMesh(resources::models::rock5),
		resourceManager.getOrLoadTexture("models/mushroom_gun/Gun(Front).png"),
		resourceManager.getOrLoadTexture("models/rocks/rock5.png"),
		technique,
		player
	) {

}
  
void MushroomGun::onUpdateSelf(float delta_time) {
	cooldown -= delta_time;
}

}
}