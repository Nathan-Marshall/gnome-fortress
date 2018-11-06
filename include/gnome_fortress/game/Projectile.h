#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshNode.h"

namespace gnome_fortress {
namespace game {

class Projectile : public model::BasicMeshNode {
public: 
    Projectile(const model::Mesh *mesh,
        const model::Texture *diffuse_texture,
        renderer::BasicMeshNodeTechnique *technique,
        glm::vec3 pointOfOrigin, glm::vec3 velocity);

    ~Projectile();

	glm::vec3 getVelocity();

    void onUpdateSelf(float delta_time) override;

private:
	const static int DAMAGE;
	double lifespan;
	glm::vec3 velocity;

	model::BasicMeshNode *mesh;

};

}
}