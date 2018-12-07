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
#include <irrKlang.h>
#include "Spore.h"
#include "Rocket.h"

namespace gnome_fortress {
namespace game {


class Enemies : public model::SceneNode {

public:
    using IncreaseScoreHandler = std::function<void(int)>;

    Enemies(Walls* walls, const IncreaseScoreHandler &increaseScoreHandler, irrklang::ISoundEngine *soundEngine);

    //Reference to the walls to be used for collisions
    Walls* walls;

    //Vectors to keep track of all the different enemies that we have
    std::vector<SiegeTurtle*> turtles;
    std::vector<Squirrel*> squirrels;
    std::vector<Spider*> spiders;

    //Methods to process enemy collisions
    void ProcessCollisions(Projectiles *projectiles, float delta_time);
    void ProcessProjectileCollisions(Projectiles *projectiles);
    void ProcessAOECollisions(std::vector<std::pair<SporeGround*, float>>* poisons, std::vector<std::pair<RocketGround*, float>>* explosions, float delta_time);
    void ProcessWallCollisions();

protected:


private:
    // Callback to update the score
    IncreaseScoreHandler increaseScoreHandler;

    //Reference to the main sound engine so we can play attack sounds
    irrklang::ISoundEngine *soundEngine;
};


}
}