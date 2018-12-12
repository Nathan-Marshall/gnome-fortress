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


class Squirrel : public game::Enemy {

public:
    Squirrel(
            resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            Walls* walls,
            irrklang::ISoundEngine *soundEngine,
            float healthMultiplier);

    //Whether or not the squirrel is hitting a wall
    bool hittingWall;
    bool onTheMove;

    //Whether or not the squirrel is at the acorn pile
    bool hittingPile;

    Walls* walls;

    //Damage that the squirrel will do upon hitting a wall
    float damageOnHit;
    
    int currentRing;

    float orbitDeg;

protected:
    void onUpdateSelf(float dt) override;


private:

};


}
}