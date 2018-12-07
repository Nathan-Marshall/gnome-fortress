#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/quaternion.hpp>

#include <functional>
#include <vector>

#include "gnome_fortress/renderer/SpriteTechnique.h"
#include "gnome_fortress/ui/UINode.h"

namespace gnome_fortress {
namespace ui {

class SpriteNode : public UINode {
public:
    SpriteNode(const model::Texture *texture, GLuint vbo, renderer::SpriteTechnique *technique);

    void setMainTexture(const model::Texture *texture);

    renderer::SpriteTechnique *getTechnique() const;

protected:

    // instructions for what to do when drawing self, after applying transformations (does not include drawing children)
    virtual void onDrawSelf(const glm::mat3 &parent_transform, unsigned int pass) const;

private:
    const model::Texture *mainTexture;
    GLuint screenQuadVBO;
    renderer::SpriteTechnique *technique;
};

}
}