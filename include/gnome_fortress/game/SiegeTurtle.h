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


class SiegeTurtle : public game::Enemy {

public:
    SiegeTurtle(
            resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            irrklang::ISoundEngine *soundEngine);

    //Whether or not the turtle is hitting a wall
    bool hittingWall;

    bool hittingPile;

    //Damage that the turtle will do upon hitting a wall
    float damageOnHit;

protected:
    void onUpdateSelf(float dt) override;

private:

};


}
}