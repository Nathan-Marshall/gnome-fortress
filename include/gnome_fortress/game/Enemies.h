#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#include <functional>

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
    using IncreaseScoreHandler = std::function<void(int)>;

    Enemies(Walls* walls, const IncreaseScoreHandler &increaseScoreHandler, irrklang::ISoundEngine *soundEngine);

    Walls* walls;

    std::vector<SiegeTurtle*> turtles;
    std::vector<Squirrel*> squirrels;
    std::vector<Spider*> spiders;

    void ProcessCollisions(Projectiles *projectiles);
    void ProcessProjectileCollisions(Projectiles *projectiles);
    void ProcessWallCollisions();
protected:


private:
    IncreaseScoreHandler increaseScoreHandler;
    irrklang::ISoundEngine *soundEngine;
};


}
}