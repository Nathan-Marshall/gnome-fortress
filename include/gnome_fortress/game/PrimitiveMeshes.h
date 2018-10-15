#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace game {

// Create the geometry of a cube centered at (0, 0, 0) with sides of length 1
model::Mesh *CreateCube(void);


// Create the geometry of a cylinder centered at (0, 0, 0) with diameter and height of 1
model::Mesh *CreateCylinder(void);

}
}