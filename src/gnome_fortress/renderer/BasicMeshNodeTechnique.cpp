#include "gnome_fortress/renderer/BasicMeshNodeTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

BasicMeshNodeTechnique::BasicMeshNodeTechnique(
        GLuint program,
        const std::string &proj_name,
        const std::string &view_name,
        const std::string &model_name,
        const std::string &normal_name,
        const std::string &eye_pos_name,
        const std::string &diffuse_color_name,
        const std::string &specular_color_name,
        const std::string &specular_exponent_name,
        const std::string &diffuse_map_name,
        const std::string &diffuse_map_on_name,
        const std::string &gloss_map_name,
        const std::string &gloss_map_on_name)
    : BasicProjectionTechnique(program, proj_name, view_name, model_name, normal_name, eye_pos_name),
      diffuse_color(0, 0, 0),
      specular_color(0, 0, 0),
      specular_exponent(0),
      diffuse_map_index(0),
      diffuse_map_on(0),
      gloss_map_index(1),
      gloss_map_on(0) {

    addUniform(Uniform(program, diffuse_color_name, GL_FLOAT, 1, 3, 1), glm::value_ptr(diffuse_color));
    addUniform(Uniform(program, specular_color_name, GL_FLOAT, 1, 3, 1), glm::value_ptr(specular_color));
    addUniform(Uniform(program, specular_exponent_name, GL_FLOAT, 1, 1, 1), &specular_exponent);
    addUniform(Uniform(program, diffuse_map_name, GL_INT, 1, 1, 1), &diffuse_map_index);
    addUniform(Uniform(program, diffuse_map_on_name, GL_INT, 1, 1, 1), &diffuse_map_on);
    addUniform(Uniform(program, gloss_map_name, GL_INT, 1, 1, 1), &gloss_map_index);
    addUniform(Uniform(program, gloss_map_on_name, GL_INT, 1, 1, 1), &gloss_map_on);
}

void BasicMeshNodeTechnique::setDiffuseColor(const glm::vec3 &color) {
    diffuse_color = color;
}

void BasicMeshNodeTechnique::setSpecularColor(const glm::vec3 &color) {
    specular_color = color;
}

void BasicMeshNodeTechnique::setSpecularExponent(GLfloat exponent) {
    specular_exponent = exponent;
}

void BasicMeshNodeTechnique::bindDiffuseTexture(const model::Texture *texture) {
    glActiveTexture(GL_TEXTURE0); // activate the first texture
    diffuse_map_on = texture == nullptr ? 0 : 1;
    bindTexture(texture);
}

void BasicMeshNodeTechnique::bindGlossTexture(const model::Texture *texture) {
    glActiveTexture(GL_TEXTURE1); // activate the second texture
    gloss_map_on = texture == nullptr ? 0 : 1;
    bindTexture(texture);
}

void BasicMeshNodeTechnique::bindTexture(const model::Texture *texture) {
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