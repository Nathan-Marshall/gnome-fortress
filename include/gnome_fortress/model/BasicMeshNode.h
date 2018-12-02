#pragma once

#include "gnome_fortress/renderer/BasicMeshNodeTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace model {

class BasicMeshNode : public SceneNode {
public:
    BasicMeshNode(
            const model::Mesh *mesh,
            renderer::BasicMeshNodeTechnique *technique);

    void onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const override;

    const model::Mesh *getMesh() const;

    renderer::BasicMeshNodeTechnique *getTechnique() const;

    void setEnvMapFactor(float factor);

private:
    const model::Mesh *mesh;
    float env_map_factor;
    renderer::BasicMeshNodeTechnique *technique;
};

}
}