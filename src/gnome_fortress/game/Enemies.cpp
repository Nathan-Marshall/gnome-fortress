#include "gnome_fortress/game/Enemies.h"
#include <iostream>
namespace gnome_fortress {
namespace game {


Enemies::Enemies(Walls* walls, const IncreaseScoreHandler &increaseScoreHandler, irrklang::ISoundEngine *soundEngine)
    : walls(walls),
      turtles(),
      squirrels(),
      spiders(),
      increaseScoreHandler(increaseScoreHandler),
      soundEngine(soundEngine) {
}

Enemies::~Enemies() {
    for each (auto turtle in turtles) {
        delete turtle;
    }
    for each (auto squirrel in squirrels) {
        delete squirrel;
    }
    for each (auto spider in spiders) {
        delete spider;
    }
}

//Process enemy collisions witth projectiles (and their AOE damage areas) and walls
void Enemies::ProcessCollisions(Projectiles *projectiles, float delta_time) {

    //Process any collisions with player fired projectiles
    ProcessProjectileCollisions(projectiles);

    //Process with AOE effects (poison, explosions)
    ProcessAOECollisions(projectiles->GetPoisons(), projectiles->GetExplosions(), delta_time);

    //Process any collisions with the walls
    ProcessWallCollisions();
}

//Process collisions between enemies and projectiles fired by the player
void Enemies::ProcessProjectileCollisions(Projectiles *projectiles) {
    bool collision = false;

    //Create iterators to loop through all 3 types of enemies
    std::vector<SiegeTurtle*>::iterator turtleIt;
    std::vector<Squirrel*>::iterator squirrelIt;
    std::vector<Spider*>::iterator spiderIt;

    std::vector<Projectile*>::iterator projecIt;

    //Check collisions with turtles
    for (turtleIt = turtles.begin(); turtleIt < turtles.end();) {
        for (projecIt = projectiles->projectiles.begin(); projecIt < projectiles->projectiles.end();) {
            collision = false;

            //There is a collision if the distance between the projectile and the enemy is less than the bounding radius (projectile radius is negligible)
            if (glm::length((*projecIt)->getPosition() - (*turtleIt)->getPosition()) <= (*turtleIt)->GetBoundingRadius()) {
                collision = true;
            }

            //Remove the projectile, do damage to the enemy, and create a new damage effect area if the projectile is a spore or rocket
            if (collision) {
                (*turtleIt)->DoDamage((*projecIt)->GetDamage());

                Spore* s = dynamic_cast<Spore*>((*projecIt));
                Rocket* r = dynamic_cast<Rocket*>((*projecIt));

                if (s) {
                    projectiles->CreatePoison(s);
                }
                else if (r) {
                    projectiles->CreateExplosion(r);
                }

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
            if (increaseScoreHandler) {
                increaseScoreHandler(100);
            }
        }
        else {
            turtleIt++;
        }
    }

    for (squirrelIt = squirrels.begin(); squirrelIt < squirrels.end();) {
        for (projecIt = projectiles->projectiles.begin(); projecIt < projectiles->projectiles.end();) {
            collision = false;

            //There is a collision if the distance between the projectile and the enemy is less than the bounding radius (projectile radius is negligible)
            if (glm::length((*projecIt)->getPosition() - (*squirrelIt)->getPosition()) <= (*squirrelIt)->GetBoundingRadius() * 1.25) {
                collision = true;
            }

            //Remove the projectile, do damage to the enemy, and create a new damage effect area if the projectile is a spore or rocket
            if (collision) {
                (*squirrelIt)->DoDamage((*projecIt)->GetDamage());

                Spore* s = dynamic_cast<Spore*>((*projecIt));
                Rocket* r = dynamic_cast<Rocket*>((*projecIt));

                if (s) {
                    projectiles->CreatePoison(s);
                }
                else if (r) {
                    projectiles->CreateExplosion(r);
                }

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
            if (increaseScoreHandler) {
                increaseScoreHandler(100);
            }
        }
        else {
            squirrelIt++;
        }
    }

    for (spiderIt = spiders.begin(); spiderIt < spiders.end();) {
        for (projecIt = projectiles->projectiles.begin(); projecIt < projectiles->projectiles.end();) {
            collision = false;

            //There is a collision if the distance between the projectile and the enemy is less than the bounding radius (projectile radius is negligible)
            if (glm::length((*projecIt)->getPosition() - (*spiderIt)->getPosition()) <= (*spiderIt)->GetBoundingRadius() * 1.25) {
                collision = true;
            }

            //Remove the projectile, do damage to the enemy, and create a new damage effect area if the projectile is a spore or rocket
            if (collision) {
                (*spiderIt)->DoDamage((*projecIt)->GetDamage());

                Spore* s = dynamic_cast<Spore*>((*projecIt));
                Rocket* r = dynamic_cast<Rocket*>((*projecIt));

                if (s) {
                    projectiles->CreatePoison(s);
                }
                else if (r) {
                    projectiles->CreateExplosion(r);
                }

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
            if (increaseScoreHandler) {
                increaseScoreHandler(100);
            }
        }
        else {
            spiderIt++;
        }
    }
}

//Process collisions between enemies and walls
void Enemies::ProcessWallCollisions() {
    bool collision = false;

    std::vector<std::vector<Wall*>> *wallVec = walls->GetWalls();

    std::vector<SiegeTurtle*>::iterator turtleIt;
    std::vector<Squirrel*>::iterator squirrelIt;
    std::vector<Spider*>::iterator spiderIt;

    std::vector<std::vector<Wall*>>::iterator wallIt;
    std::vector<Wall*>::iterator innerWallIt;

    //We want to keep track of which ring we are in
    int ringCount = 0;

    for (turtleIt = turtles.begin(); turtleIt < turtles.end(); turtleIt++) {
        ringCount = 0;
        for (wallIt = wallVec->begin(); wallIt < wallVec->end(); wallIt++) {
            ringCount++;
            for (innerWallIt = wallIt->begin(); innerWallIt < wallIt->end();) {
                glm::vec3 turtlePos = (*turtleIt)->getPosition();
                glm::vec3 wallPos = (*innerWallIt)->getPosition();

                float distance = glm::length(turtlePos - wallPos);

                float bound = (*turtleIt)->GetBoundingRadius() * 1.25;
                if (distance < bound && (*turtleIt)->hittingWall == false) {
                    //We have a collision, do damage and play attack sound
                    (*turtleIt)->hittingWall = true;
                    (*innerWallIt)->DoDamage((*turtleIt)->damageOnHit);

                    (*turtleIt)->PlayAttackSound();

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

                float distance = glm::length(squirrelPos - wallPos);

                float bound = (*squirrelIt)->GetBoundingRadius();
                if (distance < bound && (*squirrelIt)->hittingWall == false) {
                    //We have a collision, do damage and play attack sound
                    (*squirrelIt)->hittingWall = true;
                    (*innerWallIt)->DoDamage((*squirrelIt)->damageOnHit);

                    (*squirrelIt)->PlayAttackSound();

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
                float heightDiff = ((*spiderIt)->getPosition().y) - Walls::WALL_HEIGHT / 3;

                bool inside = (glm::length(wallPos - glm::vec3(0, 0, 0)) > glm::length(spiderPos - glm::vec3(0, 0, 0)));
                
                //Spiders won'tt damage walls, instead we modify spider booleans to inform the spider of where it currently is
                //and the spider will make use of this in its state machine
                if (widthDistance < (*spiderIt)->GetBoundingRadius() / 3 && heightDiff < 0 && !inside) {
                    (*spiderIt)->hittingWall = true;
                }
                if (heightDiff > 0 && !inside) {
                    (*spiderIt)->overWall = true;
                }
                if (heightDiff > 0 && inside && widthDistance < (Walls::WALL_WIDTH * 2)) {
                    (*spiderIt)->overWall = false;
                }
                innerWallIt++;
            }
        }
    }
}

//Process collisions between enemies and damaging area of effect attacks from the player
void Enemies::ProcessAOECollisions(std::vector<std::pair<SporeGround*, float>> *poisons, std::vector<std::pair<RocketGround*, float>> *explosions, float delta_time) {
    std::vector<SiegeTurtle*>::iterator turtleIt;
    std::vector<Squirrel*>::iterator squirrelIt;
    std::vector<Spider*>::iterator spiderIt;

    std::vector<std::pair<SporeGround*, float>>::iterator poisonIt;
    std::vector<std::pair<RocketGround*, float>>::iterator exploIt;

    //Get the damage and radius for our poison and explosions
    float pRad = Spore::DAMAGE_RAD;
    float pDmg = Spore::POISON_DAMAGE;

    float rRad = Rocket::DAMAGE_RAD;
    float rDmg = Rocket::EXPLOSION_DAMAGE;

    //Check if we are intersecting with any of the AOE positions with turtles
    for (turtleIt = turtles.begin(); turtleIt < turtles.end();) {
        glm::vec3 turtPos = (*turtleIt)->getPosition();
        for (poisonIt = poisons->begin(); poisonIt < poisons->end(); poisonIt++) {
            if (glm::length(turtPos - (*poisonIt).first->getPosition()) < pRad + (*turtleIt)->GetBoundingRadius()) {
                (*turtleIt)->DoDamage(pDmg * delta_time);
            }
        }
        for (exploIt = explosions->begin(); exploIt < explosions->end(); exploIt++) {
            if (glm::length(turtPos - (*exploIt).first->getPosition()) < rRad + (*turtleIt)->GetBoundingRadius()) {
                (*turtleIt)->DoDamage(rDmg * delta_time);
            }
        }

        //Remove them if they have no health
        if ((*turtleIt)->GetHealth() <= 0.0f) {
            (*turtleIt)->removeFromParent();
            turtleIt = turtles.erase(turtleIt);
            if (increaseScoreHandler) {
                increaseScoreHandler(100);
            }
        }
        else {
            turtleIt++;
        }
    }
    //Check if we are intersecting with any of the AOE positions with squirrels
    for (squirrelIt = squirrels.begin(); squirrelIt < squirrels.end();) {
        glm::vec3 squirPos = (*squirrelIt)->getPosition();
        for (poisonIt = poisons->begin(); poisonIt < poisons->end(); poisonIt++) {
            if (glm::length(squirPos - (*poisonIt).first->getPosition()) < pRad) {
                (*squirrelIt)->DoDamage(pDmg * delta_time);
            }
        }
        for (exploIt = explosions->begin(); exploIt < explosions->end(); exploIt++) {
            if (glm::length(squirPos - (*exploIt).first->getPosition()) < pRad) {
                (*squirrelIt)->DoDamage(rDmg * delta_time);
            }
        }

        //Remove them if they have no health
        if ((*squirrelIt)->GetHealth() <= 0.0f) {
            (*squirrelIt)->removeFromParent();
            squirrelIt = squirrels.erase(squirrelIt);
            if (increaseScoreHandler) {
                increaseScoreHandler(100);
            }
        }
        else {
            squirrelIt++;
        }
    }
    //Check if we are intersecting with any of the AOE positions with spiders
    for (spiderIt = spiders.begin(); spiderIt < spiders.end();) {
        glm::vec3 spiPos = (*spiderIt)->getPosition();
        for (poisonIt = poisons->begin(); poisonIt < poisons->end(); poisonIt++) {
            if (glm::length(spiPos - (*poisonIt).first->getPosition()) < pRad) {
                (*spiderIt)->DoDamage(pDmg * delta_time);
            }
        }
        for (exploIt = explosions->begin(); exploIt < explosions->end(); exploIt++) {
            if (glm::length(spiPos - (*exploIt).first->getPosition()) < pRad) {
                (*spiderIt)->DoDamage(rDmg * delta_time);
            }
        }

        //Remove them if they have no health
        if ((*spiderIt)->GetHealth() <= 0.0f) {
            (*spiderIt)->removeFromParent();
            spiderIt = spiders.erase(spiderIt);
            if (increaseScoreHandler) {
                increaseScoreHandler(100);
            }
        }
        else {
            spiderIt++;
        }
    }
}


}
}