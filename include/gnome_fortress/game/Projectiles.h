#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <algorithm>

#include "Projectile.h"

namespace gnome_fortress {
	namespace game {


		class Projectiles {

		public:
			Projectiles();

			std::vector<Projectile*> projectiles;

		protected:


		private:

		};


	}
}