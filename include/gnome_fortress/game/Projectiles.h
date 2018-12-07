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

            //Get the current poisons and explosions
            std::vector<std::pair<SporeGround*, float>>* GetPoisons();
            std::vector<std::pair<RocketGround*, float>>* GetExplosions();

            //Create poison AOE effect where the given spore is located
            void CreatePoison(Spore* spore);
            PurpleRocketStream* Projectiles::CreatePoisonTrail(Spore* spore);

            //Create an explosion where the given rocket is located
            void CreateExplosion(Rocket* rocket);

            //Create a rocket trail effect
            RocketStream* Projectiles::CreateRocketTrail(Rocket* rocket);

            //Create a shotgun trail effect
            ShotgunStream* Projectiles::CreateShotgunTrail(Rock* rock);

            void ProcessCollisions(Walls* walls);
        protected:


        private:
            //Reference to our resource manager
            resource::ResourceManager *res_man;

            //Vectors to keep track of our AOE effects
            std::vector<std::pair<SporeGround*, float>>* poisonPositions;
            std::vector<std::pair<RocketGround*, float>>* explosPositions;

            //References for all of the effects our guns can create
            SporeGroundTechnique *sporeGroundEffect;
            RocketGroundTechnique *rocketGroundEffect;
            RocketStreamTechnique *rocketStreamEffect;
            PurpleRocketStreamTechnique *purpleRocketStreamEffect;
            ShotgunStreamTechnique *shotgunStreamEffect;
        };


    }
}