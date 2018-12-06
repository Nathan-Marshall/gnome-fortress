#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#include "Projectile.h"
#include "Walls.h"
#include "Spore.h"
#include "Rocket.h"
#include "Rock.h"

#include "SporeGround.h"
#include "RocketGround.h"
#include "RocketStream.h"
#include "PurpleRocketStream.h"
#include "ShotgunStream.h"

#include "gnome_fortress/resource/ResourceManager.h"
#include "Resources.h"

namespace gnome_fortress {
    namespace game {
 
        class Projectiles : public model::SceneNode {

        public:
            Projectiles(resource::ResourceManager *resource_manager, SporeGroundTechnique *sporeGroundTech, 
            RocketGroundTechnique *rocketGroundTech, RocketStreamTechnique *rocketStreamTech, 
            PurpleRocketStreamTechnique *purpleRocketStreamTech, ShotgunStreamTechnique *shotgunStreamTech);

            void onUpdateSelf(float delta_time) override;

            std::vector<Projectile*> projectiles;

            std::vector<std::pair<SporeGround*, float>>* GetPoisons();
            std::vector<std::pair<RocketGround*, float>>* GetExplosions();

            void CreatePoison(Spore* spore);
            PurpleRocketStream* Projectiles::CreatePoisonTrail(Spore* spore);

            void CreateExplosion(Rocket* rocket);
            RocketStream* Projectiles::CreateRocketTrail(Rocket* rocket);

            ShotgunStream* Projectiles::CreateShotgunTrail(Rock* rock);

            void ProcessCollisions(Walls* walls);
        protected:


        private:
            resource::ResourceManager *res_man;

            std::vector<std::pair<SporeGround*, float>>* poisonPositions;
            std::vector<std::pair<RocketGround*, float>>* explosPositions;

            SporeGroundTechnique *sporeGroundEffect;
            RocketGroundTechnique *rocketGroundEffect;
            RocketStreamTechnique *rocketStreamEffect;
            PurpleRocketStreamTechnique *purpleRocketStreamEffect;
            ShotgunStreamTechnique *shotgunStreamEffect;
        };


    }
}