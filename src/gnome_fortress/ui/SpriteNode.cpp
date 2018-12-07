#include "gnome_fortress/ui/SpriteNode.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace gnome_fortress {
namespace ui {

// === PUBLIC ===

SpriteNode::SpriteNode(const model::Texture *texture, renderer::SpriteTechnique *technique)
    : UINode(),
      uv_min(0, 0),
      uv_max(1, 1),
      mainTexture(texture),
      technique(technique) {
}

void SpriteNode::setMainTexture(const model::Texture *texture) {
    mainTexture = texture;
}

void SpriteNode::setUVMin(const glm::vec2 &uv) {
    uv_min = uv;
}
void SpriteNode::setUVMax(const glm::vec2 &uv) {
    uv_max = uv;
}

renderer::SpriteTechnique *SpriteNode::getTechnique() const {
    return technique;
}

void SpriteNode::onDrawSelf(const glm::mat3 &parent_transform, unsigned int pass) const {
    // only draw during the first pass
    if (pass != 0) {
        return;
    }

    // ignore z-buffer
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    // bind vbo
    technique->bindScreenQuadVBO();

    // set uniforms and bind textures
    technique->setUVMin(uv_min);
    technique->setUVMax(uv_max);
    technique->bindMainTexture(mainTexture);

    // update model matrix
    technique->setModelMatrix(parent_transform * getTransformMatrix());

    // draw using technique
    technique->activate();
    glDrawArrays(GL_QUADS, 0, 4);
    technique->deactivate();
}

}
}