#include "gnome_fortress/game/Acorns.h"
#include <iostream>

namespace gnome_fortress {
namespace game {

Acorns::Acorns(resource::ResourceManager &resourceManager, renderer::BasicMeshNodeTechnique *technique)
    : acorns(NUM_ACORNS) {

    // Add acorns to the pile
    for (int i = 0; i < NUM_ACORNS; i++) {
        acorns[i] = new Acorn(resourceManager, technique);
        appendChild(acorns[i]);
    }

    acorns[0]->setPosition(0, 0.3, 0);
    acorns[1]->setPosition(.45, 0.3, 0.45);
    acorns[2]->setPosition(-.40, 0.3, 0.55);
    acorns[3]->setPosition(-.40, 0.3, -0.55);
    acorns[4]->setPosition(.43, 0.3, -0.63);
    acorns[5]->setPosition(.87, 0.3, -0.10);
    acorns[6]->setPosition(-.87, 0.3, 0);
    acorns[7]->setPosition(-.48, 0.75, -0.025);
    acorns[8]->setPosition(.48, 0.75, -0.025);
    acorns[9]->setPosition(0, 0.75, 0.45);
    acorns[10]->setPosition(0.1, 0.75, -0.55);
    acorns[11]->setPosition(0, 1.15, 0);
}

Acorns::~Acorns(){
    for each (auto acorn in acorns) {
        delete acorn;
    }
}

//Process enemies colliding with the acorns
void Acorns::ProcessEnemyCollisions(Enemies* enemies, float delta_time) {

    //Iterator for each enemy type
    std::vector<SiegeTurtle*>::iterator turtleIter;
    std::vector<Spider*>::iterator spiderIter;
    std::vector<Squirrel*>::iterator squirrelIter;

    //Process collisions with the acorns for each enemy type
    for (turtleIter = enemies->turtles.begin(); turtleIter < enemies->turtles.end();) {
    
        if (acorns.size() > 0) {
            if (glm::length((*turtleIter)->getPosition() - glm::vec3(0, 0, 0)) < 4.0) {
                acorns.back()->takeDamage(delta_time);
                (*turtleIter)->hittingPile = true;
            }
            
            if (acorns.back()->getCurrentHealth() <= 0) {
                acorns.back()->removeFromParent();
                acorns.back()->vanishScale();
                acorns.pop_back();
            }
        }
        turtleIter++;
    }

    for (spiderIter = enemies->spiders.begin(); spiderIter < enemies->spiders.end();) {
        if (acorns.size() > 0) {
            if (glm::length((*spiderIter)->getPosition() - glm::vec3(0, 0, 0)) < 1.3) {
                acorns.back()->takeDamage(delta_time);
                (*spiderIter)->hittingPile = true; 
            }

            if (acorns.back()->getCurrentHealth() <= 0) {
                acorns.back()->removeFromParent();
                acorns.back()->vanishScale();
                acorns.pop_back();
            }
        }
        spiderIter++;
    }

    for (squirrelIter = enemies->squirrels.begin(); squirrelIter < enemies->squirrels.end();) {
        if (acorns.size() > 0) {
            if (glm::length((*squirrelIter)->getPosition() - glm::vec3(0, 0, 0)) < 1.3) {
                acorns.back()->takeDamage(delta_time);
                (*squirrelIter)->hittingPile = true; 
            }

            if (acorns.back()->getCurrentHealth() <= 0) {
                acorns.back()->removeFromParent();
                acorns.back()->vanishScale();
                acorns.pop_back();
            }
        }
        squirrelIter++;
    }

}

float Acorns::getRemainingAcornCount() const {
    if (acorns.size() == 0) {
        return 0;
    }
    return acorns.size() - 1 + acorns.back()->getCurrentHealth() / Acorn::MAX_HEALTH;
}
}
} 