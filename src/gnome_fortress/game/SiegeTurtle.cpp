#include "gnome_fortress/game/SiegeTurtle.h"

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {


SiegeTurtle::SiegeTurtle(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique,
        irrklang::ISoundEngine *soundEngine)
    : game::Enemy(
        resourceManager.getOrLoadMeshGroup(resources::models::siege_turtle),
        technique
      ) {

    //Set references to the sound engine, our attack sound
    this->soundEngine = soundEngine;
    attackSoundByte = resourceManager.getOrLoadAudioClip(resources::audioClips::turtle_atk);

    //Initialize all of the physical properties of the turtles
    setScale(5.5f);

    int numWalls = Walls::NumWalls();
    float angle = ((rand() % (numWalls)) * (2 * glm::pi<float>() / numWalls));
    setPosition(glm::vec3(30 * cos(angle), 0.1, -30 * sin(angle)));
    rotate(glm::angleAxis((glm::pi<float>() / 2) + angle, glm::vec3(0, 1, 0)));

    health = 30.0f;
    boundingRadius = 2.0;
    hittingWall = false;
    damageOnHit = 20.0f;
    moveSpeed = 1.5f;

    hittingPile = false;
}

//Seige turtle update method
void SiegeTurtle::onUpdateSelf(float dt) {
    //Timer used for the animation loop
    timer += dt;

    float speed = 2.0f;
    float amp = 0.02f;

    //Front leg animations
    getChild(1)->setPosition(glm::vec3(0, amp * sin((timer * speed) + glm::pi<float>()), amp * cos((timer * speed) + glm::pi<float>())));
    getChild(1)->setOrbit(glm::angleAxis(glm::pi<float>() / 4 * sin(timer * speed + glm::pi<float>()), glm::vec3(1, 0, 0)), glm::vec3(0, 0.125, -0.22), getChild(1)->getPosition());

    getChild(4)->setPosition(glm::vec3(0, amp * sin(timer * speed), amp * cos(timer * speed)));
    getChild(4)->setOrbit(glm::angleAxis(glm::pi<float>() / 4 * sin(timer * speed), glm::vec3(1, 0, 0)), glm::vec3(0, 0.125, -0.22), getChild(4)->getPosition());
    

    //Back leg animations
    getChild(0)->setPosition(glm::vec3(0, amp * sin((timer * speed) + glm::pi<float>()), amp * cos((timer * speed) + glm::pi<float>())));
    getChild(0)->setOrbit(glm::angleAxis(glm::pi<float>() / 4 * sin(timer * speed + glm::pi<float>()), glm::vec3(1, 0, 0)), glm::vec3(0, 0.125, 0.22), getChild(0)->getPosition());

    getChild(2)->setPosition(glm::vec3(0, amp * sin(timer * speed), amp * cos(timer * speed)));
    getChild(2)->setOrbit(glm::angleAxis(glm::pi<float>() / 4 * sin(timer * speed), glm::vec3(1, 0, 0)), glm::vec3(0, 0.125, 0.22), getChild(2)->getPosition());


    //Turtle animation
    getChild(3)->setPosition(glm::vec3(0, amp * sin(timer * speed), 0));
    

    //Turtle movement
    if (hittingPile) {
        //Do nothing any more 
    }
    else if (!hittingWall) {
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