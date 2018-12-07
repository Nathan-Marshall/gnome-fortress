#include "gnome_fortress/game/Projectiles.h"

namespace gnome_fortress {
    namespace game {


        Projectiles::Projectiles(resource::ResourceManager *resource_manager, SporeGroundTechnique *sporeGroundTech, 
        RocketGroundTechnique *rocketGroundTech, RocketStreamTechnique *rocketStreamTech, 
        PurpleRocketStreamTechnique *purpleRocketStreamTech, ShotgunStreamTechnique *shotgunStreamTech) {
            //Create new vectors which will track AOE positions
            poisonPositions = new std::vector<std::pair<SporeGround*, float>>();
            explosPositions = new std::vector<std::pair<RocketGround*, float>>();

            //Set reference to the resource manager
            this->res_man = resource_manager;

            //Initialize references to all of the projectile effects to be used
            sporeGroundEffect = sporeGroundTech;
            rocketGroundEffect = rocketGroundTech;
            rocketStreamEffect = rocketStreamTech;
            purpleRocketStreamEffect = purpleRocketStreamTech;
            shotgunStreamEffect = shotgunStreamTech;
        }

        //Projectile update functions
        void Projectiles::onUpdateSelf(float delta_time) {
            std::vector<Projectile*>::iterator projecIt;

            for (projecIt = projectiles.begin(); projecIt < projectiles.end();) {
                //Remove projectiles who have been alive longer than their lifespan threshold
                if ((*projecIt)->GetLifespan() > (*projecIt)->GetDeathThreshold()) {
                    //Remove the old projectile
                    (*projecIt)->removeFromParent();
                    projecIt = projectiles.erase(projecIt);
                }
                //Remove projectiles that have hit the ground
                else if ((*projecIt)->getPosition().y < 0.1) {
                    //Create poison or explosions where the projectiles impacted
                    Spore* s = dynamic_cast<Spore*>((*projecIt));
                    Rocket* r = dynamic_cast<Rocket*>((*projecIt));

                    if (s) {
                        CreatePoison(s);
                    }
                    else if (r) {
                        CreateExplosion(r);
                    }

                    //remove the projectile, the AOE effect will persist on it's own and is now a separate entity
                    (*projecIt)->removeFromParent();
                    projecIt = projectiles.erase(projecIt);
                }
                else {
                    projecIt++;
                }
            }

            //Subtract the lifespans of all of the current poisons and explosions
            std::vector<std::pair<SporeGround*, float>>::iterator poisonIt;
            std::vector<std::pair<RocketGround*, float>>::iterator exploIt;

            for (poisonIt = poisonPositions->begin(); poisonIt < poisonPositions->end();) {
                (*poisonIt).second = (*poisonIt).second - delta_time;

                if ((*poisonIt).second <= 0) {
                    //We remove it from the vector if it's ttoo old
                    (*poisonIt).first->removeFromParent();
                    poisonIt = poisonPositions->erase(poisonIt);
                }
                else {
                    poisonIt++;
                }
            }

            for (exploIt = explosPositions->begin(); exploIt < explosPositions->end();) {
                (*exploIt).second = (*exploIt).second - delta_time;

                if ((*exploIt).second <= 0) {
                    //We remove it from the vector
                    (*exploIt).first->removeFromParent();
                    exploIt = explosPositions->erase(exploIt);
                }
                else {
                    exploIt++;
                }
            }

        }

        //Get all of the currentt poison effects
        std::vector<std::pair<SporeGround*, float>>* Projectiles::GetPoisons() {
            return poisonPositions;
        }

        //Get all of the current explosions
        std::vector<std::pair<RocketGround*, float>>* Projectiles::GetExplosions() {
            return explosPositions;
        }

        //Create a poison based on the given spore (mainly its location)
        void Projectiles::CreatePoison(Spore* spore) {
            glm::vec3 sporePos = spore->getPosition();

            //Create a new spore effect using the sporeGroundEffect technique
            SporeGround *sporeEffect = new SporeGround(res_man->getOrLoadTexture(resources::textures::flame4x4), sporeGroundEffect);
            appendChild(sporeEffect);
            sporeEffect->setPosition(sporePos.x, sporePos.y + 0.3, sporePos.z);

            //Add this new poison cloud to our vector that is tracking poisons, and initialize its lifespan
            poisonPositions->push_back(std::make_pair(sporeEffect, Spore::POISON_LIFESPAN));
        }

        //Create an explosion based on the given rocket (mainly its location)
        void Projectiles::CreateExplosion(Rocket* rocket) {
            glm::vec3 rocketPos = rocket->getPosition();

            //Create a new rocket effect using the rocketGroundEffect technique
            RocketGround *rocketEffect = new RocketGround(res_man->getOrLoadTexture(resources::textures::flame4x4), rocketGroundEffect);
            appendChild(rocketEffect);
            rocketEffect->setPosition(rocketPos.x, rocketPos.y + 0.2, rocketPos.z);

            //Add this new explosion to our vector that is tracking explosions, and initialize its lifespan
            explosPositions->push_back(std::make_pair(rocketEffect, Rocket::EXPLOSION_LIFESPAN));
        }

        //Create a poison trail to attach to moving spores (prjectiles fired from the mushroom gun)
        PurpleRocketStream* Projectiles::CreatePoisonTrail(Spore* spore) {
            glm::vec3 sporePos = spore->getPosition();

            PurpleRocketStream *poisonEffect = new PurpleRocketStream(res_man->getOrLoadTexture(resources::textures::flame4x4), purpleRocketStreamEffect);
            poisonEffect->setPower(1.0);

            return poisonEffect;
        }

        //Create a rocket trail to attach to moving rockets (projectiles fired from the pinecone gun)
        RocketStream* Projectiles::CreateRocketTrail(Rocket* rocket) {
            glm::vec3 rocketPos = rocket->getPosition();

            RocketStream *rocketEffect = new RocketStream(res_man->getOrLoadTexture(resources::textures::flame4x4), rocketStreamEffect);
            rocketEffect->setPower(2.0);
            
            return rocketEffect;
        }

        //Create a shotgun bullet trail to attach to moving shotgun projectiles (projectiles shot from the peanut gun)
        ShotgunStream* Projectiles::CreateShotgunTrail(Rock* rock) {
            glm::vec3 rockPos = rock->getPosition();

            ShotgunStream *rockEffect = new ShotgunStream(res_man->getOrLoadTexture(resources::textures::flame4x4), shotgunStreamEffect);
            rockEffect->setPower(2.0);

            return rockEffect;
        }

        //Process projectile collisions with the fences
        void Projectiles::ProcessCollisions(Walls* walls) {
            std::vector<std::vector<Wall*>>::iterator wallIt;
            std::vector<Projectile*>::iterator projecIt;
            std::vector<std::pair<glm::vec3, int>>::iterator holeIt;

            bool atHole = false;

            for (wallIt = walls->walls.begin(); wallIt < walls->walls.end(); wallIt++) {
                if ((*wallIt)[0]) {
                    for (projecIt = projectiles.begin(); projecIt < projectiles.end();) {
                        glm::vec3 projecPos = (*projecIt)->getPosition();

                        glm::vec3 wallPos = (*wallIt)[0]->getPosition();

                        float wallDist = glm::length(wallPos - glm::vec3(0, 0, 0));

                        float dist = glm::length(projecPos - glm::vec3(0, 0, 0)) - wallDist;
                        float ringDist = abs(dist);

                        //Check to see if we are hitting the 'circle' for this fence ring

                        /*Since all fences for a certain ring have the same distance from the center, we use this to check if we would hit a wall, 
                        and then just check to make sure that there isn't a hole there. This ends up being easier and faster than trying to do 
                        collision with each individual wall*/

                        if (ringDist < Walls::WALL_WIDTH / 4 && projecPos.y < Walls::WALL_HEIGHT / 3.5) {
                            //Check to see if we are at a wall hole position
                            for (holeIt = walls->wallHoles.begin(); holeIt < walls->wallHoles.end(); holeIt++) {
                                float distToProjec = glm::length(projecPos - (*holeIt).first);

                                //If there is a hole, here, we need to make note, since we won't collide with this wall ring
                                if (distToProjec < (*wallIt)[0]->GetLength() / 2) {
                                    atHole = true;
                                }
                            }
                            //Create an AOE effect, and then destroy the projectile
                            if (!atHole) {
                                Spore* s = dynamic_cast<Spore*>((*projecIt));
                                Rocket* r = dynamic_cast<Rocket*>((*projecIt));

                                if (s) {
                                    CreatePoison(s);
                                }
                                else if (r) {
                                    CreateExplosion(r);
                                }

                                //We have a collision, so remove the projectile
                                (*projecIt)->removeFromParent();
                                projecIt = projectiles.erase(projecIt);
                            }
                            else {
                                projecIt++;
                            }
                        }
                        //Check to see if the projectile would be hitting our acorn pile, because we also don't want to be able to shoot through the pile
                        else if (glm::length(projecPos - glm::vec3(0, 0, 0)) < 2.0 && projecPos.y < 1.5) {
                            Spore* s = dynamic_cast<Spore*>((*projecIt));
                            Rocket* r = dynamic_cast<Rocket*>((*projecIt));

                            if (s) {
                                CreatePoison(s);
                            }
                            else if (r) {
                                CreateExplosion(r);
                            }

                            //We have a collision, so remove the projectile
                            (*projecIt)->removeFromParent();
                            projecIt = projectiles.erase(projecIt);
                        }
                        else {
                            projecIt++;
                        }
                    }
                }
            }
        }
    }
}