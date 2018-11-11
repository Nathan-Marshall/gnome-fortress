#include "gnome_fortress/game/Enemies.h"

namespace gnome_fortress {
namespace game {


Enemies::Enemies() {
    //Nothing yet
}

void Enemies::onDrawSelf(const glm::mat4 &parentTransform) const {
    for each (SiegeTurtle* turt in turtles)
    {
        turt->draw(glm::mat4());
    }
}

void Enemies::onUpdateSelf(float dt) {
    for each (SiegeTurtle* turt in turtles)
    {
        turt->update(dt);
    }
}

void Enemies::ProcessCollisions(Projectiles *projectiles) {
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
                projecIt = projectiles->projectiles.erase(projecIt);
            }
            else {
                projecIt++;
            }
        }

        //Remove them if they have no health
        if ((*turtleIt)->GetHealth() <= 0.0f) {
            turtleIt = turtles.erase(turtleIt);
        }
        else {
            turtleIt++;
        }
    }
}

}
}