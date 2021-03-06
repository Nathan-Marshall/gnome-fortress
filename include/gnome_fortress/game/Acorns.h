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
    Acorns(resource::ResourceManager &resourceManager, renderer::BasicMeshNodeTechnique *technique);

    ~Acorns();

    const static int NUM_ACORNS = 12;

    std::vector<Acorn*> acorns;

    //Process collisions between the acorns and the enemies
    void ProcessEnemyCollisions(Enemies* turtles, float delta_time);

    float getRemainingAcornCount() const;

private:

};

}
}