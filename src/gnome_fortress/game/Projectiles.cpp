#include "gnome_fortress/game/Projectiles.h"

namespace gnome_fortress {
    namespace game {


        Projectiles::Projectiles() {
            poisonPositions = new std::vector<glm::vec3>();
            explosPositions = new std::vector<glm::vec3>();
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
                else if ((*projecIt)->getPosition().y < 0) {
                    Spore* s = dynamic_cast<Spore*>((*projecIt));
                    Rocket* r = dynamic_cast<Rocket*>((*projecIt));

                    if (s) {
                        //We have a valid spore
                        poisonPositions->push_back(s->getPosition());
                    }
                    else if (r) {
                        //We have a valid rocket
                        explosPositions->push_back(r->getPosition());
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