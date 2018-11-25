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
            renderer::BasicMeshNodeTechnique *technique);

    //Whether or not the squirrel is hitting a wall
    bool hittingWall;
    bool onTheMove;

    //Damage that the squirrel will do upon hitting a wall
    float damageOnHit;
    
    int currentRing;

    void addWallHole(glm::vec3 holePos, int ringCount);

protected:
    void onUpdateSelf(float dt) override;

private:
    std::vector<std::pair<glm::vec3, int>> wallHoles;

};


}
}