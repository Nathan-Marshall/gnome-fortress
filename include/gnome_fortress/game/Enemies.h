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
#include "Spore.h"
#include "Rocket.h"

namespace gnome_fortress {
namespace game {


class Enemies : public model::SceneNode {

public:
    Enemies(Walls* walls, irrklang::ISoundEngine *soundEngine);

    Walls* walls;

    std::vector<SiegeTurtle*> turtles;
    std::vector<Squirrel*> squirrels;
    std::vector<Spider*> spiders;

    void ProcessCollisions(Projectiles *projectiles, float delta_time);
    void ProcessProjectileCollisions(Projectiles *projectiles);
    void ProcessAOECollisions(std::vector<std::pair<SporeGround*, float>>* poisons, std::vector<std::pair<RocketGround*, float>>* explosions, float delta_time);
    void ProcessWallCollisions();
protected:


private:
    irrklang::ISoundEngine *soundEngine;
};


}
}