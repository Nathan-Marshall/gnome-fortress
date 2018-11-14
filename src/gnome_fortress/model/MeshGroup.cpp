#include "gnome_fortress/model/MeshGroup.h"

namespace gnome_fortress {
namespace model {

MeshGroup::MeshGroup()
    : meshes(),
      materials() {
}

MeshGroup::MeshGroup(const std::vector<Mesh *> &meshes, const std::vector<Material *> &materials)
    : meshes(meshes),
      materials(materials) {
}

}
}