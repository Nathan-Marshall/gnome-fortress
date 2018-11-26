#include "gnome_fortress/game/Enemies.h"

namespace gnome_fortress {
namespace game {


Enemies::Enemies(Walls* walls) {
    this->walls = walls;
}

void Enemies::ProcessCollisions(Projectiles *projectiles) {

    //Process any collisions with player fired projectiles
    ProcessProjectileCollisions(projectiles);

    //Process any collisions with the walls
    ProcessWallCollisions();
}

void Enemies::ProcessProjectileCollisions(Projectiles *projectiles) {
    bool collision = false;

    std::vector<SiegeTurtle*>::iterator turtleIt;
    std::vector<Squirrel*>::iterator squirrelIt;
    std::vector<Spider*>::iterator spiderIt;

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

    for (squirrelIt = squirrels.begin(); squirrelIt < squirrels.end();) {
        for (projecIt = projectiles->projectiles.begin(); projecIt < projectiles->projectiles.end();) {
            collision = false;

            if (glm::length((*projecIt)->getPosition() - (*squirrelIt)->getPosition()) <= (*squirrelIt)->GetBoundingRadius()) {
                collision = true;
            }

            if (collision) {
                (*squirrelIt)->DoDamage((*projecIt)->GetDamage());

                //Remove the projectile
                (*projecIt)->removeFromParent();
                projecIt = projectiles->projectiles.erase(projecIt);
            }
            else {
                projecIt++;
            }
        }

        //Remove them if they have no health
        if ((*squirrelIt)->GetHealth() <= 0.0f) {
            (*squirrelIt)->removeFromParent();
            squirrelIt = squirrels.erase(squirrelIt);
        }
        else {
            squirrelIt++;
        }
    }

    for (spiderIt = spiders.begin(); spiderIt < spiders.end();) {
        for (projecIt = projectiles->projectiles.begin(); projecIt < projectiles->projectiles.end();) {
            collision = false;

            if (glm::length((*projecIt)->getPosition() - (*spiderIt)->getPosition()) <= (*spiderIt)->GetBoundingRadius()) {
                collision = true;
            }

            if (collision) {
                (*spiderIt)->DoDamage((*projecIt)->GetDamage());

                //Remove the projectile
                (*projecIt)->removeFromParent();
                projecIt = projectiles->projectiles.erase(projecIt);
            }
            else {
                projecIt++;
            }
        }

        //Remove them if they have no health
        if ((*spiderIt)->GetHealth() <= 0.0f) {
            (*spiderIt)->removeFromParent();
            spiderIt = spiders.erase(spiderIt);
        }
        else {
            spiderIt++;
        }
    }
}

void Enemies::ProcessWallCollisions() {
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
                float bound = (*turtleIt)->GetBoundingRadius();
                if (distance < bound && (*turtleIt)->hittingWall == false) {
                    //We have a collision
                    (*turtleIt)->hittingWall = true;
                    (*innerWallIt)->DoDamage((*turtleIt)->damageOnHit);

                    if ((*innerWallIt)->GetHealth() <= 0) {
                        //We need to remove the wall
                        (*innerWallIt)->removeFromParent();

                        walls->wallHoles.push_back(std::make_pair((*innerWallIt)->getPosition(), ringCount));

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

                glm::vec3 wallLeftPos = wallPos + (glm::vec3(-(*innerWallIt)->GetLength()/2, 0, 0) * (*innerWallIt)->getRotation());
                glm::vec3 wallRightPos = wallPos + (glm::vec3((*innerWallIt)->GetLength()/2, 0, 0) * (*innerWallIt)->getRotation());

                float distance = glm::length(squirrelPos - wallPos);
                float distLeft = glm::length(squirrelPos - wallLeftPos);
                float distRight = glm::length(squirrelPos - wallRightPos);

                //float bound = (*squirrelIt)->GetBoundingRadius();
                float bound = 1.25f;
                if ((distance < bound || distLeft < bound || distRight < bound) && (*squirrelIt)->hittingWall == false) {
                    //We have a collision
                    (*squirrelIt)->hittingWall = true;
                    (*innerWallIt)->DoDamage((*squirrelIt)->damageOnHit);

                    if ((*innerWallIt)->GetHealth() <= 0) {
                        //We need to remove the wall
                        walls->wallHoles.push_back(std::make_pair((*innerWallIt)->getPosition(), ringCount));

                        (*innerWallIt)->removeFromParent();
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
                float heightDiff = ((*spiderIt)->getPosition().y) - Walls::WALL_HEIGHT/2;

                if (widthDistance < (*spiderIt)->GetBoundingRadius() && heightDiff < (*spiderIt)->GetBoundingRadius()/2 && (*spiderIt)->hittingWall == false) {
                    (*spiderIt)->hittingWall = true;
                }
                else if (heightDiff >(*spiderIt)->GetBoundingRadius() / 2) {
                    (*spiderIt)->overWall = true;
                }
                else {
                    (*spiderIt)->overWall = false;
                }
                innerWallIt++;
            
            }
        }
    }
}


}
}