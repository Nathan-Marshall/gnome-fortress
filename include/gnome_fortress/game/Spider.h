#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <cstdlib>

#include "gnome_fortress/game/Enemy.h"
#include "gnome_fortress/game/Walls.h"
#include "gnome_fortress/resource/ResourceManager.h"

namespace gnome_fortress {
namespace game {


class Spider : public game::Enemy {

public:
    Spider(
            resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique);

    bool hittingWall;

    bool overWall;

protected:
    void onUpdateSelf(float dt) override;

private:

};


}
}