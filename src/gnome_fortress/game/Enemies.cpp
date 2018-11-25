#include "gnome_fortress/game/Enemies.h"

namespace gnome_fortress {
namespace game {


Enemies::Enemies() {
    wallHoles = new std::vector<std::pair<glm::vec3, int>>();
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
    std::vector<Squirrel*>::iterator squirrelIt;
    std::vector<Spider*>::iterator spiderIt;

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

                        wallHoles->push_back(std::make_pair((*innerWallIt)->getPosition(), ringCount));

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

    for (squirrelIt = squirrels.begin(); squirrelIt < squirrels.end(); squirrelIt++) {
        ringCount = 0;
        for (wallIt = wallVec->begin(); wallIt < wallVec->end(); wallIt++) {
            ringCount++;
            for (innerWallIt = wallIt->begin(); innerWallIt < wallIt->end();) {
                glm::vec3 squirrelPos = (*squirrelIt)->getPosition();
                glm::vec3 wallPos = (*innerWallIt)->getPosition();

                float distance = glm::length(squirrelPos - wallPos);

                //Need to change this back later once nathans stuff is working
                //if (distance < (*turtleIt)->GetBoundingRadius()){
                if (distance < 1.5f && (*squirrelIt)->hittingWall == false) {
                    //We have a collision
                    (*squirrelIt)->hittingWall = true;
                    (*innerWallIt)->DoDamage((*squirrelIt)->damageOnHit);

                    if ((*innerWallIt)->GetHealth() <= 0) {
                        //We need to remove the wall
                        (*innerWallIt)->removeFromParent();

                        wallHoles->push_back(std::make_pair((*innerWallIt)->getPosition(), ringCount));

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

    for (spiderIt = spiders.begin(); spiderIt < spiders.end(); spiderIt++) {
        for (wallIt = wallVec->begin(); wallIt < wallVec->end(); wallIt++) {
            for (innerWallIt = wallIt->begin(); innerWallIt < wallIt->end();) {
                glm::vec3 spiderPos = (*spiderIt)->getPosition();
                glm::vec3 wallPos = (*innerWallIt)->getPosition();

                spiderPos.y = 0;
                wallPos.y = 0;

                float widthDistance = glm::length(spiderPos - wallPos);

                if (widthDistance < (*spiderIt)->GetBoundingRadius() && ((*spiderIt)->getPosition().y < Walls::WALL_HEIGHT) && (*spiderIt)->hittingWall == false) {
                    (*spiderIt)->hittingWall = true;
                }
                else if (((*spiderIt)->getPosition().y >= Walls::WALL_HEIGHT)) {
                    (*spiderIt)->overWall = true;
                }

                innerWallIt++;
            
            }
        }
    }
}


}
}