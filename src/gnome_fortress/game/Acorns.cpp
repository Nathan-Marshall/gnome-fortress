#include "gnome_fortress/game/Acorns.h"
#include <iostream>

namespace gnome_fortress {
namespace game {

Acorns::Acorns() {
    //Nothing right now 
}

void Acorns::ProcessEnemyCollisions(Enemies* enemies) {

    std::vector<SiegeTurtle*>::iterator turtleIter;
    std::vector<Spider*>::iterator spiderIter;
    std::vector<Squirrel*>::iterator squirrelIter;

    for (turtleIter = enemies->turtles.begin(); turtleIter < enemies->turtles.end();) {
    
        if (acorns.size() > 0) {
            if (glm::length((*turtleIter)->getPosition() - glm::vec3(0, 0, 0)) < 4.0) {
                acorns.back()->takeDamage();
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
                acorns.back()->takeDamage();
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
                acorns.back()->takeDamage();
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
} //namespace game
} //namespace gnome_fortress 