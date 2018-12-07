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

    //Draw method for the skybox
    void onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const override;

    const model::Mesh *getMesh() const;

    renderer::SkyboxTechnique *getTechnique() const;

private:
    //Generate a mesh for the skybox
    static model::Mesh *GenerateMesh();

    //The mesh, texture, and technique used for rendering the skybox
    const model::Mesh *mesh;
    const Texture *texture;
    renderer::SkyboxTechnique *technique;
};

}
}