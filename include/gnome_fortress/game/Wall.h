#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshNode.h"

namespace gnome_fortress {
	namespace game {

		class Wall : public model::BasicMeshNode {

		public:
			Wall(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique, float wallHealth = 100);

		protected:
			void onUpdateSelf(float dt) override;

		private:
			float health;
		};
	}
}