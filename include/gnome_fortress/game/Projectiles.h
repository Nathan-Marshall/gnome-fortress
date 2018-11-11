#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#include "Projectile.h"

namespace gnome_fortress {
    namespace game {


        class Projectiles : public model::SceneNode {

        public:
            Projectiles();

            std::vector<Projectile*> projectiles;

            void onDrawSelf(const glm::mat4 &parent_transform) const override;
            void onUpdateSelf(float delta_time) override;

        protected:


        private:

        };


    }
}