#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#include "Projectile.h"
#include "Spore.h"
#include "Rocket.h"
#include "Rock.h"

namespace gnome_fortress {
    namespace game {
 
        class Projectiles : public model::SceneNode {

        public:
            Projectiles();

            void onUpdateSelf(float delta_time) override;

            std::vector<Projectile*> projectiles;

            std::vector<glm::vec3>* GetPoisons();
            std::vector<glm::vec3>* GetExplosions();

        protected:


        private:
            std::vector<glm::vec3> poisonPositions;
            std::vector<glm::vec3> explosPositions;
        };


    }
}