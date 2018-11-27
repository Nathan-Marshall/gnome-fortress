#pragma once

#include "gnome_fortress/renderer/BasicMeshNodeTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace model {

class SkyboxNode : public SceneNode {
public:
    SkyboxNode(
            const model::Mesh *mesh,
            renderer::BasicMeshNodeTechnique *technique);

    void onDrawSelf(const glm::mat4 &parent_transform) const override;

    const model::Mesh *getMesh() const;

    renderer::BasicMeshNodeTechnique *getTechnique() const;

private:
    const model::Mesh *mesh;
    renderer::BasicMeshNodeTechnique *technique;
};

}
}