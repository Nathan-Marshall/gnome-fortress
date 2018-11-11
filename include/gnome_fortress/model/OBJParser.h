#pragma once

#include <string>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "gnome_fortress/model/MeshGroup.h"

namespace gnome_fortress {

namespace resource {
    class ResourceManager;
}

namespace model {

MeshGroup LoadMesh(const std::string &filename, resource::ResourceManager &resourceManager);

}
}