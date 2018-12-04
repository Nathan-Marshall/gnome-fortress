#include "gnome_fortress/game/Projectiles.h"

namespace gnome_fortress {
    namespace game {


        Projectiles::Projectiles(resource::ResourceManager *resource_manager, SporeGroundTechnique *sporeGroundTech, RocketGroundTechnique *rocketGroundTech) {
            poisonPositions = new std::vector<std::pair<SporeGround*, float>>();
            explosPositions = new std::vector<std::pair<RocketGround*, float>>();

            this->res_man = resource_manager;

            sporeGroundEffect = sporeGroundTech;
            rocketGroundEffect = rocketGroundTech;
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
                        glm::vec3 sporePos = s->getPosition();

                        SporeGround *sporeEffect = new SporeGround(res_man->getOrLoadTexture(resources::textures::flame4x4), sporeGroundEffect);
                        appendChild(sporeEffect);
                        sporeEffect->setPosition(sporePos.x, sporePos.y + 0.3, sporePos.z);

                        poisonPositions->push_back(std::make_pair(sporeEffect, Spore::POISON_LIFESPAN));
                    }
                    else if (r) {
                        glm::vec3 rocketPos = r->getPosition();

                        RocketGround *rocketEffect = new RocketGround(res_man->getOrLoadTexture(resources::textures::flame4x4), rocketGroundEffect);
                        appendChild(rocketEffect);
                        rocketEffect->setPosition(rocketPos.x, rocketPos.y + 0.2, rocketPos.z);


                        explosPositions->push_back(std::make_pair(rocketEffect, Rocket::EXPLOSION_LIFESPAN));

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
    }
}