#include "gnome_fortress/game/Spider.h"

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {


    Spider::Spider(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique)
    : game::Enemy(
        resourceManager.getOrLoadMeshGroup(resources::models::siege_turtle),
        technique
      ) {

    setScale(2.0f);

    int numWalls = Walls::NumWalls();
    float angle = ((rand() % (numWalls)) * (2 * glm::pi<float>() / numWalls));
    setPosition(glm::vec3(30 * cos(angle), -0.2, -30 * sin(angle)));
    rotate(glm::angleAxis((glm::pi<float>() / 2) + angle, glm::vec3(0, 1, 0)));

    health = 10.0f;
    boundingRadius = (sqrt(3) * 2) / 2;
    moveSpeed = 2.0f;
    hittingWall = false;
    hittingPile = false;
}

void Spider::onUpdateSelf(float dt) {
    if (hittingPile) {
        //Do nothing any more 
    }
    else if (!hittingWall) {
        glm::vec3 moveDir = glm::normalize(getPosition() - glm::vec3(0, 0.1, 0));

        if (overWall) {
            translate(glm::vec3(-moveDir.x, -0.1, -moveDir.z) * dt);
            overWall = false;
        }
        else if (getPosition().y > 0.1) {
            translate(glm::vec3(0, -1, 0) * dt);
            hittingWall = false;
        }
        else {
            //For now, the spider will just move to the origin
            glm::vec3 vel = moveDir * moveSpeed;
            translate(glm::vec3(-vel.x, -vel.y, -vel.z) * dt);
        }
    }
    else {
        //move up a bit, and reset the flag
        translate(glm::vec3(0, 1, 0) * dt);
        hittingWall = false;
    }
}


}
}