#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Wall.h";

namespace gnome_fortress {
namespace game {

class Walls : public model::SceneNode {

public:
	Walls(const model::Mesh *mesh,
            const model::Texture *diffuse_texture,
            renderer::BasicMeshNodeTechnique *technique,
            int numRings = 3);

	//Vector to define the walls
	std::vector<std::vector<Wall*>> walls;

	void onDrawSelf(const glm::mat4 &parent_transform) const override;
	void onUpdateSelf(float delta_time) override;
protected:
			
private:
	const static float OUTER_RADIUS;
	const static float INNER_RADIUS;
	const static int WALLS_PER_RING;

	void FillWalls(
            const model::Mesh *mesh,
            const model::Texture *diffuse_texture,
            renderer::BasicMeshNodeTechnique *technique,
            int numRings);
};


}
}