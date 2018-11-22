#include "gnome_fortress/renderer/BasicMeshNodeTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

BasicMeshNodeTechnique::BasicMeshNodeTechnique(
        GLuint program,
        const std::string &proj_name,
        const std::string &view_name,
        const std::string &model_name,
        const std::string &diffuse_name)
    : BasicProjectionTechnique(program, proj_name, view_name, model_name),
      diffuse_texture_index(0) {

    addUniform(Uniform(program, diffuse_name, GL_INT, 1, 1, 1), &diffuse_texture_index);
}

void BasicMeshNodeTechnique::bindDiffuseTexture(const model::Texture *texture) {
    glActiveTexture(GL_TEXTURE0); // activate the first texture
    glBindTexture(GL_TEXTURE_2D, texture->id); // bind the active texture
    // Define texture interpolation
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

}
}