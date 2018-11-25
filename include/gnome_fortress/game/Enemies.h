#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#include "Enemy.h"
#include "Projectiles.h"
#include "Walls.h"
#include "SiegeTurtle.h"
#include "Squirrel.h"

namespace gnome_fortress {
namespace game {


class Enemies : public model::SceneNode {

public:
    Enemies();

    std::vector<std::pair<glm::vec3, int>> *wallHoles;

    std::vector<SiegeTurtle*> turtles;
    std::vector<Squirrel*> squirrels;

    void ProcessCollisions(Projectiles *projectiles, Walls *walls);
    void ProcessProjectileCollisions(Projectiles *projectiles);
    void ProcessWallCollisions(Walls *walls);
protected:


private:

};


}
}