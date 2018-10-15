#include "gnome_fortress/model/BasicMeshNode.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace model {

BasicMeshNode::BasicMeshNode(
        const Mesh *mesh,
        renderer::BasicProjectionTechnique *technique)
    : mesh(mesh),
      technique(technique) {

}

void BasicMeshNode::onDrawSelf(const glm::mat4 &parent_transform) const {
    if (mesh) {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);

        technique->setModelMatrix(parent_transform * getTransformMatrix());
        technique->activate();
        glDrawElements(mesh->mode, mesh->num_elements, GL_UNSIGNED_INT, 0);
        technique->deactivate();
    }
}

const Mesh *BasicMeshNode::getMesh() const {
    return mesh;
}

renderer::BasicProjectionTechnique *BasicMeshNode::getTechnique() const {
    return technique;
}

}
}