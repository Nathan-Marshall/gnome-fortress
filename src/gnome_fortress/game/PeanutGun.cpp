#include "gnome_fortress/game/PeanutGun.h"
#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {
PeanutGun::PeanutGun(
       resource::ResourceManager &resourceManager,
       renderer::BasicMeshNodeTechnique *technique,
       Player *player)
    : game::Weapon(
        resourceManager.getOrLoadMeshGroup(resources::models::peanut_gun),
        resourceManager.getOrLoadMeshGroup(resources::models::rock1),
        technique,
        player
    ) {

}

void PeanutGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;
}

}
}