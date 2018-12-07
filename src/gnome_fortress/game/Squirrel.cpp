#include "gnome_fortress/game/Squirrel.h"

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {


Squirrel::Squirrel(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        Walls* walls, irrklang::ISoundEngine *soundEngine)
    : game::Enemy(
        resourceManager.getOrLoadMeshGroup(resources::models::squirrel),
        technique
      ) {

    this->soundEngine = soundEngine;
    attackSoundByte = resourceManager.getOrLoadAudioClip(resources::audioClips::squirrel_atk);

    this->walls = walls;

    setScale(2.0f);

    int numWalls = Walls::NumWalls();
    float angle = ((rand() % (numWalls)) * (2 * glm::pi<float>() / numWalls));
    setPosition(glm::vec3(30 * cos(angle), 0.2, -30 * sin(angle)));
    rotate(glm::angleAxis((glm::pi<float>() / 2) + angle, glm::vec3(0, 1, 0)));

    health = 10.0f;
    boundingRadius = (sqrt(3) / 1.5);
    hittingWall = false;
    damageOnHit = 10.0f;
    moveSpeed = 2.0f;
    currentRing = 3;

    hittingPile = false;
}

void Squirrel::onUpdateSelf(float dt) {
    timer += dt;

    if (hittingPile){ 
        //Do nothing anymore 
    }
    else if (!hittingWall) {
        //Initial values to track and help with our movement
        float shortestDist = 1000.0f;
        float shortestRing = 0.0f;
        glm::vec3 moveVec = glm::vec3(0, 0, 0);
        int sign = 1;
        glm::vec3 hole;
        //We check every hole in the walls, this vector gets updated by the collision detection in enemies
        for each(std::pair<glm::vec3, int> holeInfo in walls->wallHoles) {
            //Split up the pair to get the location, and which ring it's on
            hole = holeInfo.first;
            float ringNum = holeInfo.second;

            //Vectors in the direction of the origin, and the hole
            glm::vec3 holeVec = hole - glm::vec3(0, 0.1, 0);
            glm::vec3 origVec = getPosition() - glm::vec3(0, 0.1, 0);

            float dot = glm::dot(glm::normalize(holeVec), glm::normalize(origVec));
            glm::vec3 cross = glm::cross(holeVec, origVec);

            if (cross.y > 0) {
                sign = -1;
            }
            else {
                sign = 1;
            }

            float angle = acos(dot);

            //Distance to this hole
            float dist = glm::distance(getPosition(), hole);

            //If we have a shorter distance on the correct ring, we move to that hole.
            if (dist < shortestDist && ringNum == currentRing) {
                moveVec = getPosition() - hole;
                shortestDist = dist;
                orbitDeg = angle;
            }
        }

        //We update our ring number once we reach the hole
        if (shortestDist < 0.5 || (shortestDist != 1000 && glm::length(getPosition() - glm::vec3(0,0,0)) < glm::length(hole - glm::vec3(0,0,0)) + Walls::WALL_WIDTH)) {
            glm::vec3 moveDir = glm::normalize(getPosition() - glm::vec3(0, 0.5, 0));
            glm::vec3 vel = moveDir * moveSpeed;
            translate(glm::vec3(-vel.x, -vel.y, -vel.z) * 3.0f * dt);
            currentRing--;
            shortestDist = 1000.0f;
        }

        //Move towards the hole
        else if (shortestDist != 1000 && currentRing > 0) {
            if (orbitDeg > 0.1) {
                orbit(glm::angleAxis((sign * 10 * dt) * glm::pi<float>() / 180.0f, glm::vec3(0, 1, 0)), glm::vec3(0, 0.25, 0));
                orbitDeg -= 10 * dt;
            }
            else {
                glm::vec3 vel = glm::normalize(moveVec) * moveSpeed;
                translate(glm::vec3(-vel.x, 0.0, -vel.z) * dt);
            }
            
        }

        //Move to the origin if we are in the middle section
        else {
            glm::vec3 moveDir = glm::normalize(getPosition() - glm::vec3(0, 0.25, 0));
            glm::vec3 vel = moveDir * moveSpeed;
            translate(glm::vec3(-vel.x, -vel.y, -vel.z) * dt);
        }
    }
    else {

        //move back a bit, and reset the flag
        glm::vec3 moveDir = glm::normalize(getPosition());
        translate(glm::vec3(moveDir.x, 0.0, moveDir.z) * 1.0f);
        hittingWall = false;
    }
}


}
}