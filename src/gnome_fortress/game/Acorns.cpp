#include "gnome_fortress/game/Acorns.h"
#include <iostream>

namespace gnome_fortress {
namespace game {

Acorns::Acorns() {
    //Nothing right now 
}

void Acorns::ProcessEnemyCollisions(Enemies* turtles) {
    bool collision = false;

    std::vector<SiegeTurtle*>::iterator turtleIter;
    
    
    for (turtleIter = turtles->turtles.begin(); turtleIter < turtles->turtles.end();) {
        collision = false;

        if (acorns.size() > 0) {
            if (glm::length((*turtleIter)->getPosition() - glm::vec3(0, 0, 0)) < 1.3) {
                acorns.back()->takeDamage();
                //acorns.back()->updateStatus(true);
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
/*
void Acorns::ProcessEnemyCollisions(Enemies* turtles) {
    bool collision = false;

    std::vector<Acorn*>::iterator acornIt;
    std::vector<SiegeTurtle*>::iterator TURTIt;
    
    /*for (TURTIt = turtles->turtles.begin(); TURTIt < turtles->turtles.end();) {
        for (acornIt = acorns.begin(); acornIt < acorns.end();) {
            collision = false;
            
            if (glm::length((*acornIt)->getPosition() - (*TURTIt)->getPosition()) <= (*TURTIt)->GetBoundingRadius()) {
                collision = true;
            }

            if (collision) {
                acorns.back()->updateStatus(collision);
                /*
                if (acorns.back()->getSize() <= 0) {
                    std::cout << "acorn should be gone now" << std::endl;
                    //acorns.back()->removeFromParent();
                    //acorns.pop_back();
                    //return;
                    if (acorns.back()->getSize() > 0) {
                        //acorns.back()->shrink(0);
                        acorns.back()->shrink(acorns.back()->GetShrinkRate());
                    }
                    else {
                        acorns.back()->removeFromParent();
                        acorns.pop_back();
                        return;
                    }

                    //Remove the projectile
                    //(*acornIt)->removeFromParent();
                    //acornIt = acorns.erase(acornIt);
                }
                else {
                    acornIt++;
                }
            }
            TURTIt++;
        }* /

        
        for (TURTIt = turtles->turtles.begin(); TURTIt < turtles->turtles.end();) {
            for (acornIt = acorns.begin(); acornIt < acorns.end();) {
                collision = false;

                if (glm::length((*TURTIt)->getPosition() - (*acornIt)->getPosition()) <= (*acornIt)->GetBoundingRadius()) {
                   collision = true;
                }

                if (collision) {
                    //std::cout << "collision occurred" << std::endl;
                    /*acorns.back()->updateStatus(collision);
                    if (acorns.back()->getSize() <= 0) {
                        acorns.back()->removeFromParent();
                        acorns.pop_back();
                        return;
                    }* /
                    if (takeDamage()) {
                        acorns.back()->removeFromParent();
                        acorns.pop_back();
                        return;
                        //acornIt = acorns.erase(acornIt);
                    }
                }
                else {
                    acornIt++;
                }
            }
            TURTIt++;
        } 


        //So, loop through all the acorns 
        //If ONE of the acorns is in contact 
        //Start shriking the LAST acorn in the pile (the top ones)

         //   }
       // }
    //}
}*/
} //namespace game
} //namespace gnome_fortress 