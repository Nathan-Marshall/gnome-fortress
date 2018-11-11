#include "gnome_fortress/game/PeanutGun.h"
#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {
PeanutGun::PeanutGun(
       resource::ResourceManager &resourceManager,
       renderer::BasicMeshNodeTechnique *technique,
       Player *player)
    : game::Weapon(
        resourceManager.getOrLoadMesh(resources::models::peanut_gun),
        resourceManager.getOrLoadMesh(resources::models::rock1),
        resourceManager.getOrLoadTexture("models/peanut_gun/Gun_001.png"),
        resourceManager.getOrLoadTexture("models/rocks/rock1.png"),
        technique,
        player
    ) {

}

void PeanutGun::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;
}

}
}