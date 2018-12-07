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

    //Set value for back culling
    void setBackCulling(bool culling);

    //Set whether blending is enabled
    void setBlendingEnabled(bool enabled);

    /* Note that ambient factor values do not come from an MTL file because it is typically more of a global property
     * and if we change it, we don't want to have to do so in every MTL file. The reason it is a property at all is that
     * certain objects in the scene are exceptions that we want more ambiently lit (like tree leaves).*/
    void setAmbientFactor(float factor);
    void setEnvMapFactor(float factor);

private:
    //The mesh to be drawn for this node
    const model::Mesh *mesh;

    //Bools to track whether to blend and/or cull back faces
    bool backCulling;
    bool blendingEnabled;

    float ambient_factor;
    float env_map_factor;
    renderer::BasicMeshNodeTechnique *technique;
};

}
}