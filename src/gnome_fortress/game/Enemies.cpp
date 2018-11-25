#include "gnome_fortress/game/Enemies.h"

namespace gnome_fortress {
namespace game {


Enemies::Enemies() {
}

void Enemies::ProcessCollisions(Projectiles *projectiles, Walls *walls) {

    //Process any collisions with player fired projectiles
    ProcessProjectileCollisions(projectiles);

    //Process any collisions with the walls
    ProcessWallCollisions(walls);
}

void Enemies::ProcessProjectileCollisions(Projectiles *projectiles) {
    bool collision = false;

    std::vector<SiegeTurtle*>::iterator turtleIt;
    std::vector<Projectile*>::iterator projecIt;

    for (turtleIt = turtles.begin(); turtleIt < turtles.end();) {
        for (projecIt = projectiles->projectiles.begin(); projecIt < projectiles->projectiles.end();) {
            collision = false;

            if (glm::length((*projecIt)->getPosition() - (*turtleIt)->getPosition()) <= (*turtleIt)->GetBoundingRadius()) {
                collision = true;
            }

            if (collision) {
                (*turtleIt)->DoDamage((*projecIt)->GetDamage());

                //Remove the projectile
                (*projecIt)->removeFromParent();
                projecIt = projectiles->projectiles.erase(projecIt);
            }
            else {
                projecIt++;
            }
        }

        //Remove them if they have no health
        if ((*turtleIt)->GetHealth() <= 0.0f) {
            (*turtleIt)->removeFromParent();
            turtleIt = turtles.erase(turtleIt);
        }
        else {
            turtleIt++;
        }
    }
}

void Enemies::ProcessWallCollisions(Walls *walls) {
    bool collision = false;

    std::vector<std::vector<Wall*>> *wallVec = walls->GetWalls();

    std::vector<SiegeTurtle*>::iterator turtleIt;
    std::vector<std::vector<Wall*>>::iterator wallIt;
    std::vector<Wall*>::iterator innerWallIt;

    int ringCount = 0;

    for (turtleIt = turtles.begin(); turtleIt < turtles.end(); turtleIt++) {
        ringCount = 0;
        for (wallIt = wallVec->begin(); wallIt < wallVec->end(); wallIt++) {
            ringCount++;
            for (innerWallIt = wallIt->begin(); innerWallIt < wallIt->end();) {
                glm::vec3 turtlePos = (*turtleIt)->getPosition();
                glm::vec3 wallPos = (*innerWallIt)->getPosition();

                float distance = glm::length(turtlePos - wallPos);

                //Need to change this back later once nathans stuff is working
                //if (distance < (*turtleIt)->GetBoundingRadius()){
                if (distance < 1.5f && (*turtleIt)->hittingWall == false) {
                    //We have a collision
                    (*turtleIt)->hittingWall = true;
                    (*innerWallIt)->DoDamage((*turtleIt)->damageOnHit);

                    if ((*innerWallIt)->GetHealth() <= 0) {
                        //We need to remove the wall
                        (*innerWallIt)->removeFromParent();

                        for each (Squirrel* squir in squirrels) {
                            squir->addWallHole((*innerWallIt)->getPosition(), ringCount);
                        }

                        innerWallIt = (*wallIt).erase(innerWallIt);
                    }
                }
                else {
                    innerWallIt++;
                }
            }
        }
    }
}


}
}