#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"
#include "gnome_fortress/renderer/Basic2DTechnique.h"

namespace gnome_fortress {
namespace renderer {

class SpriteTechnique : public Basic2DTechnique {
public:
    SpriteTechnique(GLuint program, GLuint screenQuadVBO);

    void bindScreenQuadVBO();

    void bindMainTexture(const model::Texture *texture);

    void setUVMin(const glm::vec2 &uv);
    void setUVMax(const glm::vec2 &uv);

protected:
    void bindTexture(const model::Texture *texture);

private:
    GLuint screenQuadVBO;
    glm::vec2 uv_min;
    glm::vec2 uv_max;
    GLint main_texture_index;
};

}
}