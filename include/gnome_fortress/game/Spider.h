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
            renderer::BasicMeshNodeTechnique *technique,
            irrklang::ISoundEngine *soundEngine,
            float healthMultiplier);

    //Booleans to track whether the spider is hitting a wall, hitting the acorn pile, or is currently over/on top of a wall
    bool hittingWall;

    bool hittingPile;

    bool overWall;

    

protected:
    void onUpdateSelf(float dt) override;

private:
    //Enum to keep track of the spider state
    enum state
    {
        INIT = 0,
        CLIMBING = 1,
        ON_WALL = 2,
        DESCENDING = 3
    };

    //The current movement/rotation state of the spider
    state state;
};


}
}