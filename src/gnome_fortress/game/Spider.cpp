#include "gnome_fortress/game/Spider.h"

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {


    Spider::Spider(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        irrklang::ISoundEngine *soundEngine)
    : game::Enemy(
        resourceManager.getOrLoadMeshGroup(resources::models::spider),
        technique
      ) {

    //Set references to the sound engine and our attack sound
    this->soundEngine = soundEngine;
    attackSoundByte = resourceManager.getOrLoadAudioClip(resources::audioClips::spider_atk);

    //Initialize physical properties for the spiders
    setScale(2.0f);

    int numWalls = Walls::NumWalls();
    float angle = ((rand() % (numWalls)) * (2 * glm::pi<float>() / numWalls));
    setPosition(glm::vec3(30 * cos(angle), -0.2, -30 * sin(angle)));
    rotate(glm::angleAxis((glm::pi<float>() / 2) + angle, glm::vec3(0, 1, 0)));

    health = 10.0f;
    boundingRadius = (sqrt(3) / 2);
    moveSpeed = 2.0f;
    hittingWall = false;
    hittingPile = false;

    state = INIT;
}

//Update method for the spiders
void Spider::onUpdateSelf(float dt) {
    //Timer to be used for animation loops (currently no animation)
    timer += dt;

    //Rotation of the spider, as well as the state changes and logic
    //The variables hittingWall and overWall are coming from the collision detection code in enemies.cpp
    if (hittingWall && state != CLIMBING) {
        translateY(0.2);
        rotate(glm::angleAxis(90 * glm::pi<float>() / 180.0f, glm::vec3(1, 0, 0)));
        state = CLIMBING;
    }
    if (overWall && state == CLIMBING) {
        rotate(glm::angleAxis(-90 * glm::pi<float>() / 180.0f, glm::vec3(1, 0, 0)));
        state = ON_WALL;
    }
    else if (getPosition().y > 0.1 && !overWall && state == ON_WALL) {
        rotate(glm::angleAxis(-90 * glm::pi<float>() / 180.0f, glm::vec3(1,0,0)));
        state = DESCENDING;
    }
    else if (getPosition().y < 0.1 && state == DESCENDING){
        rotate(glm::angleAxis(90 * glm::pi<float>() / 180.0f, glm::vec3(1, 0, 0)));
        state = INIT;
    }


    //Spider movement
    if (hittingPile) {
        //Do nothing any more 
    }
    else {
        glm::vec3 moveDir = glm::normalize(getPosition() - glm::vec3(0, 0.1, 0));

        //Move based on the current state of the spider
        if (state == INIT) {
            glm::vec3 vel = moveDir * moveSpeed;
            translate(glm::vec3(-vel.x, -vel.y, -vel.z) * dt);
        }
        else if (state == CLIMBING) {
            translate(glm::vec3(0, 1, 0) * dt);
            hittingWall = false;
        }
        else if (state == ON_WALL) {
            translate(glm::vec3(-moveDir.x, 0, -moveDir.z) * dt);
            overWall = false;
        }
        else if (state == DESCENDING) {
            translate(glm::vec3(0, -1, 0) * dt);
            hittingWall = false;
        }
    }

    Enemy::onUpdateSelf(dt);
}


}
}