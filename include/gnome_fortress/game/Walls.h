#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Wall.h";

namespace gnome_fortress {
	namespace game {

		class Walls {

		public:
			Walls(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique, int numRings = 3);

			//Vector to define the walls
			//Use a vector over an array so that the size can be dynamic, and we can change the number of rings, etc
			std::vector<std::vector<Wall*>> walls;

		protected:
			
		private:
			const static float OUTER_RADIUS;
			const static float INNER_RADIUS;
			const static int WALLS_PER_RING;

			void FillWalls(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique, int numRings);
		};
	}
}