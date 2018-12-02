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

    this->soundEngine = soundEngine;
    attackSoundByte = resourceManager.getOrLoadAudioClip(resources::audioClips::spider_atk);

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

    currentRot = 0;
}

void Spider::onUpdateSelf(float dt) {

    //Rotation of the spider
    if (hittingWall && currentRot != 1) {
        translateY(0.2);
        rotate(glm::angleAxis(90 * glm::pi<float>() / 180.0f, glm::vec3(1, 0, 0)));
        currentRot = 1;
    }
    if (overWall && currentRot == 1) {
        rotate(glm::angleAxis(-90 * glm::pi<float>() / 180.0f, glm::vec3(1, 0, 0)));
        currentRot = 2;
    }
    else if (getPosition().y > 0.1 && !overWall && currentRot == 2) {
        rotate(glm::angleAxis(-90 * glm::pi<float>() / 180.0f, glm::vec3(1,0,0)));
        currentRot = 3;
    }
    else if (getPosition().y < 0.1 && currentRot == 3){
        rotate(glm::angleAxis(90 * glm::pi<float>() / 180.0f, glm::vec3(1, 0, 0)));
        currentRot = 0;
    }

    if (hittingPile) {
        //Do nothing any more 
    }
    else {
        glm::vec3 moveDir = glm::normalize(getPosition() - glm::vec3(0, 0.1, 0));

        if (currentRot == 0) {
            glm::vec3 vel = moveDir * moveSpeed;
            translate(glm::vec3(-vel.x, -vel.y, -vel.z) * dt);
        }
        else if (currentRot == 1) {
            translate(glm::vec3(0, 1, 0) * dt);
            hittingWall = false;
        }
        else if (currentRot == 2) {
            translate(glm::vec3(-moveDir.x, 0, -moveDir.z) * dt);
            overWall = false;
        }
        else if (currentRot == 3) {
            translate(glm::vec3(0, -1, 0) * dt);
            hittingWall = false;
        }
    }
}


}
}