#include "gnome_fortress/game/Squirrel.h"

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {


Squirrel::Squirrel(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        std::vector<std::pair<glm::vec3, int>>* enemyWallHoles)
    : game::Enemy(
        resourceManager.getOrLoadMeshGroup(resources::models::siege_turtle),
        technique
      ) {

    for each (std::pair<glm::vec3, int> hole in *enemyWallHoles) {
        addWallHole(hole.first, hole.second);
    }

    setScale(2.5f);

    int numWalls = Walls::NumWalls();
    float angle = ((rand() % (numWalls)) * (2 * glm::pi<float>() / numWalls));
    setPosition(glm::vec3(30 * cos(angle), -0.2, -30 * sin(angle)));
    rotate(glm::angleAxis((glm::pi<float>() / 2) + angle, glm::vec3(0, 1, 0)));

    health = 10.0f;
    boundingRadius = sqrt(3);
    hittingWall = false;
    onTheMove = false;
    damageOnHit = 10.0f;
    moveSpeed = 2.0f;
    currentRing = 3;
}

void Squirrel::addWallHole(glm::vec3 holePos, int ringCount) {
    wallHoles.push_back(std::make_pair(holePos, ringCount));
}

void Squirrel::onUpdateSelf(float dt) {

    if (!hittingWall) {
        //Initial values to track and help with our movement
        float shortestDist = 1000.0f;
        float shortestRing = 0.0f;
        glm::vec3 moveVec = glm::vec3(0, 0, 0);

        //We check every hole in the walls, this vector gets updated by the collision detection in enemies
        for each(std::pair<glm::vec3, int> holeInfo in wallHoles) {
            //Split up the pair to get the location, and which ring it's on
            glm::vec3 hole = holeInfo.first;
            float ringNum = holeInfo.second;

            //Vectors in the direction of tthe origin, and the hole
            glm::vec3 holeVec = getPosition() - hole;
            glm::vec3 origVec = getPosition() - glm::vec3(0, 0, 0);

            //Distance to this hole
            float dist = glm::distance(getPosition(), hole);

            //Angle to move to this hole
            float angle = glm::acos(glm::dot(glm::normalize(origVec), glm::normalize(holeVec)));

            //If we have a shorter distance on the correct ring, we move to that hole.
            //until the squirrel starts moving towards a hole, we restrict that the angle 
            //must be reasonable to avoid going through walls
            if (dist < shortestDist && ringNum == currentRing && (angle < 15 * (glm::pi<float>() / 180.0f) || onTheMove)) {
                onTheMove = true;
                moveVec = holeVec;
                shortestDist = dist;
                shortestRing = ringNum;
            }
        }

        //We update our ring number once we reach the hole
        if (shortestDist < 0.1) {
            currentRing--;
            shortestDist = 1000.0f;
        }

        //Move towards the hole
        if (shortestDist != 1000 && currentRing != 0) {
            glm::vec3 vel = glm::normalize(moveVec) * moveSpeed;
            translate(glm::vec3(-vel.x, -vel.y, -vel.z) * dt);
        }

        //Move to the origin if we are in the middle section
        else {
            glm::vec3 moveDir = glm::normalize(getPosition() - glm::vec3(0, 0.1, 0));
            glm::vec3 vel = moveDir * moveSpeed;
            translate(glm::vec3(-vel.x, -vel.y, -vel.z) * dt);
        }
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