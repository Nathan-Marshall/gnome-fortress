#include "gnome_fortress/game/Projectiles.h"

namespace gnome_fortress {
    namespace game {


        Projectiles::Projectiles(resource::ResourceManager *resource_manager, SporeGroundTechnique *sporeGroundTech, RocketGroundTechnique *rocketGroundTech) {
            poisonPositions = new std::vector<glm::vec3>();
            explosPositions = new std::vector<glm::vec3>();

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

                        poisonPositions->push_back(sporePos);

                        SporeGround *sporeEffect = new SporeGround(res_man->getOrLoadTexture(resources::textures::flame4x4), sporeGroundEffect);
                        appendChild(sporeEffect);
                        sporeEffect->setPosition(sporePos.x, sporePos.y + 0.1, sporePos.z);
                    }
                    else if (r) {
                        //We have a valid rocket
                        explosPositions->push_back(r->getPosition());

                        RocketGround *rocketEffect = new RocketGround(res_man->getOrLoadTexture(resources::textures::flame4x4), rocketGroundEffect);
                        appendChild(rocketEffect);
                        rocketEffect->setPosition(r->getPosition());
                    }

                    (*projecIt)->removeFromParent();
                    projecIt = projectiles.erase(projecIt);
                }
                else {
                    projecIt++;
                }
            }
        }

        std::vector<glm::vec3>* Projectiles::GetPoisons() {
            return poisonPositions;
        }

        std::vector<glm::vec3>* Projectiles::GetExplosions() {
            return explosPositions;
        }
    }
}