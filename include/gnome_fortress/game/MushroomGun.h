#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/Weapon.h"

namespace gnome_fortress {
namespace game {

class MushroomGun : public game::Weapon {

public:
    MushroomGun(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        Player *player);

protected:
    void onUpdateSelf(float dt) override;
};

}
}