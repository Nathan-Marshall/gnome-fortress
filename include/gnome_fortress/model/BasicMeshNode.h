#pragma once

#include "gnome_fortress/renderer/BasicProjectionTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace model {

class BasicMeshNode : public SceneNode {
public:
    BasicMeshNode(
            const model::Mesh *mesh,
            renderer::BasicProjectionTechnique *technique);

    void onDrawSelf(const glm::mat4 &parent_transform) const override;

    const model::Mesh *getMesh() const;

    renderer::BasicProjectionTechnique *getTechnique() const;

private:
    const model::Mesh *mesh;
    renderer::BasicProjectionTechnique *technique;
};

}
}