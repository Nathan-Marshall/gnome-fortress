#pragma once

#include "gnome_fortress/renderer/BasicMeshNodeTechnique.h"
#include "gnome_fortress/model/BasicMeshNode.h"
#include "gnome_fortress/model/MeshGroup.h"

namespace gnome_fortress {
namespace model {

class BasicMeshGroupNode : public SceneNode {
public:
    BasicMeshGroupNode(
            const model::MeshGroup *meshGroup,
            renderer::BasicMeshNodeTechnique *technique);

    ~BasicMeshGroupNode();

    const model::MeshGroup *getMeshGroup() const;

    renderer::BasicMeshNodeTechnique *getTechnique() const;

private:
    const model::MeshGroup *meshGroup;
    renderer::BasicMeshNodeTechnique *technique;

    std::vector<BasicMeshNode *> meshNodes;
};

}
}