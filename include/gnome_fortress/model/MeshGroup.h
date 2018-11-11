#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace model {

struct MeshGroup {
    MeshGroup();

    MeshGroup(const std::vector<Mesh> &meshes, const std::vector<Material> &materials);

    std::vector<Mesh> meshes;
    std::vector<Material> materials;
};

}
}