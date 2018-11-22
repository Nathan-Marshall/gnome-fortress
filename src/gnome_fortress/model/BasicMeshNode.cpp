#include "gnome_fortress/model/BasicMeshNode.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace model {

BasicMeshNode::BasicMeshNode(
        const Mesh *mesh,
        renderer::BasicMeshNodeTechnique *technique)
    : mesh(mesh),
      technique(technique) {

}

void BasicMeshNode::onDrawSelf(const glm::mat4 &parent_transform) const {
    if (mesh) {
        // bind buffers for mesh
        glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
        
        // bind textures
        technique->setDiffuseColor(mesh->material->Kd);
        technique->setSpecularColor(mesh->material->Ks);
        technique->setSpecularExponent(mesh->material->Ns);
        technique->bindDiffuseTexture(mesh->material->map_Kd);
        technique->bindGlossTexture(mesh->material->map_Ks);

        // update model matrix
        technique->setModelMatrix(parent_transform * getTransformMatrix());

        // draw using technique
        technique->activate();
        glDrawElements(mesh->mode, mesh->num_elements, GL_UNSIGNED_INT, 0);
        technique->deactivate();
    }
}

const Mesh *BasicMeshNode::getMesh() const {
    return mesh;
}

renderer::BasicMeshNodeTechnique *BasicMeshNode::getTechnique() const {
    return technique;
}

}
}