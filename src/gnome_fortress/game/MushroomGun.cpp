#include "gnome_fortress/game/MushroomGun.h"
#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {
MushroomGun::MushroomGun(
    resource::ResourceManager &resourceManager,
    renderer::BasicMeshNodeTechnique *technique,
    Player *player)
    : game::Weapon(
        resourceManager.getOrLoadMeshGroup(resources::models::mushroom_gun),
        resourceManager.getOrLoadMeshGroup(resources::models::rock5),
        technique,
        player
    ) {

}
  
void MushroomGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;
}

}
}