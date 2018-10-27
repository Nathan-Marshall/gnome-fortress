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


class Enemies : public model::SceneNode {

public:
	Enemies();

	std::vector<SiegeTurtle*> turtles;

	void onDrawSelf(const glm::mat4 &parent_transform) const override;
	void onUpdateSelf(float delta_time) override;

protected:


private:

};


}
}