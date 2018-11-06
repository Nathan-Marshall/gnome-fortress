#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <cstdlib>

#include "gnome_fortress/game/Enemy.h"

namespace gnome_fortress {
namespace game {


class SiegeTurtle : public game::Enemy {

public:
	SiegeTurtle(const model::Mesh *mesh,
        const model::Texture *diffuse_texture,
        renderer::BasicMeshNodeTechnique *technique);

protected:
	void onUpdateSelf(float dt) override;

private:

};


}
}