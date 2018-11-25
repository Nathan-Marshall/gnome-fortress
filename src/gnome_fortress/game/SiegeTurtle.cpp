#include "gnome_fortress/game/SiegeTurtle.h"

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {


SiegeTurtle::SiegeTurtle(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique)
    : game::Enemy(
        resourceManager.getOrLoadMeshGroup(resources::models::siege_turtle),
        technique
      ) {
    setScale(2.5f);

    int numWalls = Walls::NumWalls();
    float angle = ((rand() % (numWalls)) * (2 * glm::pi<float>() / numWalls));
    setPosition(glm::vec3(30 * cos(angle), 0.1, -30 * sin(angle)));
    rotate(glm::angleAxis((glm::pi<float>() / 2) + angle, glm::vec3(0, 1, 0)));

    health = 30.0f;
    boundingRadius = sqrt(2);
    hittingWall = false;
    damageOnHit = 20.0f;
    moveSpeed = 1.5f;
}

void SiegeTurtle::onUpdateSelf(float dt) {
    if (!hittingWall) {
        //For now, the siege turtle will just move to the origin
        glm::vec3 moveDir = glm::normalize(getPosition() - glm::vec3(0, 0.1, 0));
        glm::vec3 vel = moveDir * moveSpeed;
        translate(glm::vec3(-vel.x, -vel.y, -vel.z) * dt);
    }
    else {
        //move back a bit, and reset the flag
        glm::vec3 moveDir = glm::normalize(getPosition() - glm::vec3(0, 0.1, 0));
        translate(glm::vec3(moveDir.x, moveDir.y, moveDir.z) * 1.0f);
        hittingWall = false;
    }
}


}
}