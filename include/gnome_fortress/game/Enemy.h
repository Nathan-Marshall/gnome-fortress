#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshNode.h"

namespace gnome_fortress {
namespace game {


class Enemy : public model::BasicMeshNode {

public:
	Enemy(const model::Mesh *mesh,
        const model::Texture *diffuse_texture,
		renderer::BasicMeshNodeTechnique *technique);

	float GetBoundingRadius();
	float GetHealth();
	void DoDamage(float damage);

protected:
	void onUpdateSelf(float dt) override;

	float health;
	float boundingRadius;

private:
	
};


}
}