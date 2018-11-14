#include "gnome_fortress/model/BasicMeshGroupNode.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace model {

BasicMeshGroupNode::BasicMeshGroupNode(
        const MeshGroup *meshGroup,
        renderer::BasicMeshNodeTechnique *technique)
    : meshGroup(meshGroup),
      technique(technique),
      meshNodes() {

    // create one or more BasicMeshNodes as children of this BasicMeshGroupNode
    for (auto mesh : meshGroup->meshes) {
        BasicMeshNode *meshNode = new BasicMeshNode(mesh, technique);
        appendChild(meshNode);
        meshNodes.push_back(meshNode);
    }
}

BasicMeshGroupNode::~BasicMeshGroupNode() {
    for (auto meshNode : meshNodes) {
        delete meshNode;
    }
}

const MeshGroup *BasicMeshGroupNode::getMeshGroup() const {
    return meshGroup;
}

renderer::BasicMeshNodeTechnique *BasicMeshGroupNode::getTechnique() const {
    return technique;
}

}
}