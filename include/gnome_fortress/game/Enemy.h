#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshGroupNode.h"

namespace gnome_fortress {
namespace game {


class Enemy : public model::BasicMeshGroupNode {

public:
	Enemy(const model::MeshGroup *meshGroup,
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