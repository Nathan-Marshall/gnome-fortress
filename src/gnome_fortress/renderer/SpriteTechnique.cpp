#include "gnome_fortress/renderer/SpriteTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

SpriteTechnique::SpriteTechnique(GLuint program)
    : Basic2DTechnique(program),
      main_texture_index(0) {

    addUniform(Uniform(program, "main_texture", GL_INT, 1, 1, 1), &main_texture_index);

    addVertexAttribute(renderer::VertexAttribute(program, "vertex", 2, GL_FLOAT, GL_FALSE));
    addVertexAttribute(renderer::VertexAttribute(program, "uv", 2, GL_FLOAT, GL_FALSE));
}

void SpriteTechnique::bindMainTexture(const model::Texture *texture) {
    glActiveTexture(GL_TEXTURE0); // activate the first texture
    bindTexture(texture);
}

void SpriteTechnique::bindTexture(const model::Texture *texture) {
    if (texture) {
        glBindTexture(GL_TEXTURE_2D, texture->id); // bind the active texture
        // Define texture interpolation
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

}
}