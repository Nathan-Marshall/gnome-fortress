#pragma once

#include "gnome_fortress/renderer/SkyboxTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace model {

class Skybox : public SceneNode {
public:
    Skybox(const Texture *texture, renderer::SkyboxTechnique *technique);
    ~Skybox();

    void onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const override;

    const model::Mesh *getMesh() const;

    renderer::SkyboxTechnique *getTechnique() const;

private:
    static model::Mesh *GenerateMesh();

    const model::Mesh *mesh;
    const Texture *texture;
    renderer::SkyboxTechnique *technique;
};

}
}