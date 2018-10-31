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
	SiegeTurtle(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique);

protected:
	void onUpdateSelf(float dt) override;

private:

};


}
}