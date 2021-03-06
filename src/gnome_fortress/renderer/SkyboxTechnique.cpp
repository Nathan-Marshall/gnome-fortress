#include "gnome_fortress/renderer/SkyboxTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

SkyboxTechnique::SkyboxTechnique(GLuint program)
    : BasicProjectionTechnique(program),
      cube_map_index(0) {

    addUniform(Uniform(program, "cube_map", GL_INT, 1, 1, 1), &cube_map_index);

    addVertexAttribute(renderer::VertexAttribute(program, "vertex", 3, GL_FLOAT, GL_FALSE));
    addVertexAttribute(renderer::VertexAttribute(program, "normal", 3, GL_FLOAT, GL_FALSE));
}

void SkyboxTechnique::bindSkyboxTexture(const model::Texture *texture) {
    glActiveTexture(GL_TEXTURE0); // activate the first texture

    if (texture) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture->id); // bind the active texture
        // Define texture interpolation
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}

}
}