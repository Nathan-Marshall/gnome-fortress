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
		renderer::BasicMeshNodeTechnique *technique);

protected:
	void onUpdateSelf(float dt) override;

private:
	float health;
	
};


}
}