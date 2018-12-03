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
#include "Spider.h"
#include "irrKlang\irrKlang.h"

namespace gnome_fortress {
namespace game {


class Enemies : public model::SceneNode {

public:
    Enemies(Walls* walls, irrklang::ISoundEngine *soundEngine);

    Walls* walls;

    std::vector<SiegeTurtle*> turtles;
    std::vector<Squirrel*> squirrels;
    std::vector<Spider*> spiders;

    void ProcessCollisions(Projectiles *projectiles);
    void ProcessProjectileCollisions(Projectiles *projectiles);
    void ProcessAOECollisions(std::vector<glm::vec3>* poisons, std::vector<glm::vec3>* explosions);
    void ProcessWallCollisions();
protected:


private:
    irrklang::ISoundEngine *soundEngine;
};


}
}