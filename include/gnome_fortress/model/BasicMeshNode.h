#pragma once

#include "gnome_fortress/renderer/BasicMeshNodeTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/Mesh.h"
#include "gnome_fortress/model/Texture.h"

namespace gnome_fortress {
namespace model {

class BasicMeshNode : public SceneNode {
public:
    BasicMeshNode(
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