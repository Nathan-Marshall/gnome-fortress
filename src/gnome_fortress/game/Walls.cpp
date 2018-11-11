#include "gnome_fortress/game/Walls.h"

namespace gnome_fortress {
namespace game {


const float Walls::INNER_RADIUS = 7.0f;
const float Walls::OUTER_RADIUS = 22.0f;
const int Walls::WALLS_PER_RING = 15;

Walls::Walls(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        int numRings){
    FillWalls(resourceManager, technique, numRings);
}

//Add the walls to the walls vector, based off of the number of rings and the defined constants
void Walls::FillWalls(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        int numRings) {
    //Calculate the distance between each ring
    float distPerRing = (OUTER_RADIUS - INNER_RADIUS) / numRings;
            
    for (int i = 0; i < numRings; i++) {
        //Calculate the radius for this ring
        float ringRadius = distPerRing * i + INNER_RADIUS;

        //Calculate the width of each wall for this ring to remove large gaps between the walls
        float wallWidth = (2 * glm::pi<float>() * ringRadius) / WALLS_PER_RING;
  
        //Create a new vector to store this ring
        std::vector<Wall*> *wallRing = new std::vector<Wall*>();

        //Create, move and orient the walls for this ring
        for (int j = 0; j < WALLS_PER_RING; j++) {
            Wall *wall = new Wall(resourceManager, technique);

            float angle = j * ((2 * glm::pi<float>()) / WALLS_PER_RING);
            float orientAngle = ((90 - j * (360 / WALLS_PER_RING)) * glm::pi<float>() / 180.0f);
            wall->rotate(orientAngle, glm::vec3(0, 1, 0));
            wall->setPosition(glm::vec3(ringRadius * (cos(angle)), 0.5, ringRadius * sin(angle)));
            wall->setScale(glm::vec3(wallWidth, 3, 0.5));
            wallRing->push_back(wall);
            this->appendChild(wall);
        }
                
        //Add this ring to the walls
        walls.push_back(*wallRing);
    }
}

void Walls::onUpdateSelf(float dt) {
    //Walls don't do anything to update at all yet
}

}
}