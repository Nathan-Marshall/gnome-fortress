#include "gnome_fortress/game/Walls.h"

namespace gnome_fortress {
	namespace game {
		const float Walls::INNER_RADIUS = 5.0f;
		const float Walls::OUTER_RADIUS = 22.0f;
		const int Walls::WALLS_PER_RING = 5;

		Walls::Walls(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique, int numRings){
			FillWalls(mesh, technique, numRings);
		}

		void Walls::FillWalls(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique, int numRings) {
			float distPerRing = (OUTER_RADIUS - INNER_RADIUS) / numRings;
			
			for (int i = 0; i < numRings; i++) {
				float wallWidth = (2 * glm::pi<float>() * (distPerRing * (i + 1))) / WALLS_PER_RING;
  
				std::vector<Wall*> *wallRing = new std::vector<Wall*>();

				for (int j = 0; j < WALLS_PER_RING; j++) {
					Wall *wall = new Wall(mesh, technique);

					float angle = j * ((2 * glm::pi<float>()) / WALLS_PER_RING);
					float orientAngle = ((90 - j * (360 / WALLS_PER_RING)) * glm::pi<float>() / 180.0f);
					wall->rotate(orientAngle, glm::vec3(0, 1, 0));
					wall->setPosition(glm::vec3((distPerRing * (i + 1)) * (cos(angle)), 0.5, (distPerRing * (i + 1)) * sin(angle)));
					wall->setScale(glm::vec3(wallWidth, 1, 1));
					wallRing->push_back(wall);
				}

				walls.push_back(*wallRing);
			}
		}
	}
}