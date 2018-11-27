#include "gnome_fortress/game/Acorns.h"
#include <iostream>

namespace gnome_fortress {
namespace game {

Acorns::Acorns() {
    //Nothing right now 
}

void Acorns::ProcessEnemyCollisions(Enemies* turtles) {

    std::vector<SiegeTurtle*>::iterator turtleIter;
    
    
    for (turtleIter = turtles->turtles.begin(); turtleIter < turtles->turtles.end();) {
    
        if (acorns.size() > 0) {
            if (glm::length((*turtleIter)->getPosition() - glm::vec3(0, 0, 0)) < 1.3) {
                acorns.back()->takeDamage();
                (*turtleIter)->hittingWall = true;
            }
            
            if (acorns.back()->getCurrentHealth() <= 0) {
                acorns.back()->removeFromParent();
                acorns.back()->vanishScale();
                acorns.pop_back();
            }
        }
        turtleIter++;
    }
}
} //namespace game
} //namespace gnome_fortress 