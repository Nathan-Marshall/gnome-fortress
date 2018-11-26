#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Wall.h"

namespace gnome_fortress {
namespace game {

class Walls : public model::SceneNode {

public:
    const static float OUTER_RADIUS;
    const static float INNER_RADIUS;
    const static int WALLS_PER_RING;
    const static float WALL_WIDTH;
    const static float WALL_HEIGHT;

    Walls(  resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            int numRings = 3);

    //Vector to define the walls
    std::vector<std::vector<Wall*>> walls;
    std::vector<std::pair<glm::vec3, int>> wallHoles;

    void onUpdateSelf(float delta_time) override;

    std::vector<std::vector<Wall*>>* GetWalls();

    static int NumWalls();
protected:
            
private:
    void FillWalls(
            resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            int numRings);
};


}
}