#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#include "Enemy.h"
#include "SiegeTurtle.h"

namespace gnome_fortress {
namespace game {


class Enemies {

public:
	Enemies();

	std::vector<SiegeTurtle*> turtles;

protected:


private:

};


}
}