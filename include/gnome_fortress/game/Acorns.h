#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#include "Acorn.h"
#include "Enemies.h"

namespace gnome_fortress {
namespace game {

class Acorns : public model::SceneNode {

public:
    Acorns();

    std::vector<Acorn*> acorns;

    void ProcessEnemyCollisions(Enemies* turtles);

private:
    bool underAttack;

    //Need a function to actually make sure they start getting removed 

    //So, loop through all the acorns 
    //If ONE of the acorns is in contact 
    //Start shriking the LAST acorn in the pile (the top ones)

};

}
}