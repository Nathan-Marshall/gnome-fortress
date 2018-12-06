#include "gnome_fortress/game/Projectiles.h"

namespace gnome_fortress {
    namespace game {


        Projectiles::Projectiles(resource::ResourceManager *resource_manager, SporeGroundTechnique *sporeGroundTech, 
        RocketGroundTechnique *rocketGroundTech, RocketStreamTechnique *rocketStreamTech, 
        PurpleRocketStreamTechnique *purpleRocketStreamTech, ShotgunStreamTechnique *shotgunStreamTech) {
            poisonPositions = new std::vector<std::pair<SporeGround*, float>>();
            explosPositions = new std::vector<std::pair<RocketGround*, float>>();

            this->res_man = resource_manager;

            sporeGroundEffect = sporeGroundTech;
            rocketGroundEffect = rocketGroundTech;
            rocketStreamEffect = rocketStreamTech;
            purpleRocketStreamEffect = purpleRocketStreamTech;
            shotgunStreamEffect = shotgunStreamTech;
        }

        void Projectiles::onUpdateSelf(float delta_time) {
            std::vector<Projectile*>::iterator projecIt;

            for (projecIt = projectiles.begin(); projecIt < projectiles.end();) {
                double lifespane = (*projecIt)->GetLifespan();

                if ((*projecIt)->GetLifespan() > (*projecIt)->GetDeathThreshold()) {
                    //Remove the old projectile
                    (*projecIt)->removeFromParent();
                    projecIt = projectiles.erase(projecIt);
                }
                else if ((*projecIt)->getPosition().y < 0.1) {
                    Spore* s = dynamic_cast<Spore*>((*projecIt));
                    Rocket* r = dynamic_cast<Rocket*>((*projecIt));

                    if (s) {
                        CreatePoison(s);
                    }
                    else if (r) {
                        CreateExplosion(r);
                    }

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
                    //We remove it from the vector
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

        std::vector<std::pair<SporeGround*, float>>* Projectiles::GetPoisons() {
            return poisonPositions;
        }

        std::vector<std::pair<RocketGround*, float>>* Projectiles::GetExplosions() {
            return explosPositions;
        }

        void Projectiles::CreatePoison(Spore* spore) {
            glm::vec3 sporePos = spore->getPosition();

            SporeGround *sporeEffect = new SporeGround(res_man->getOrLoadTexture(resources::textures::flame4x4), sporeGroundEffect);
            appendChild(sporeEffect);
            sporeEffect->setPosition(sporePos.x, sporePos.y + 0.3, sporePos.z);

            poisonPositions->push_back(std::make_pair(sporeEffect, Spore::POISON_LIFESPAN));
        }

        void Projectiles::CreateExplosion(Rocket* rocket) {
            glm::vec3 rocketPos = rocket->getPosition();

            RocketGround *rocketEffect = new RocketGround(res_man->getOrLoadTexture(resources::textures::flame4x4), rocketGroundEffect);
            appendChild(rocketEffect);
            rocketEffect->setPosition(rocketPos.x, rocketPos.y + 0.2, rocketPos.z);

            explosPositions->push_back(std::make_pair(rocketEffect, Rocket::EXPLOSION_LIFESPAN));
        }

        PurpleRocketStream* Projectiles::CreatePoisonTrail(Spore* spore) {
            glm::vec3 sporePos = spore->getPosition();

            PurpleRocketStream *poisonEffect = new PurpleRocketStream(res_man->getOrLoadTexture(resources::textures::flame4x4), purpleRocketStreamEffect);
            poisonEffect->setPower(1.0);

            return poisonEffect;
        }

        RocketStream* Projectiles::CreateRocketTrail(Rocket* rocket) {
            glm::vec3 rocketPos = rocket->getPosition();

            RocketStream *rocketEffect = new RocketStream(res_man->getOrLoadTexture(resources::textures::flame4x4), rocketStreamEffect);
            rocketEffect->setPower(2.0);
            
            return rocketEffect;
        }

        ShotgunStream* Projectiles::CreateShotgunTrail(Rock* rock) {
            glm::vec3 rockPos = rock->getPosition();

            ShotgunStream *rockEffect = new ShotgunStream(res_man->getOrLoadTexture(resources::textures::flame4x4), shotgunStreamEffect);
            rockEffect->setPower(2.0);

            return rockEffect;
        }
    }
}