#include "gnome_fortress/renderer/BasicMeshNodeTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

BasicMeshNodeTechnique::BasicMeshNodeTechnique(GLuint program)
    : BasicProjectionTechnique(program),
      ambient_factor(0),
      diffuse_color(0, 0, 0),
      specular_color(0, 0, 0),
      specular_exponent(0),
      alpha(1),
      diffuse_map_index(0),
      diffuse_map_on(0),
      gloss_map_index(1),
      gloss_map_on(0),
      alpha_map_index(2),
      alpha_map_on(0),
      env_map(nullptr),
      env_map_index(3),
      env_map_factor(0) {

    addUniform(Uniform(program, "ambient_factor", GL_FLOAT, 1, 1, 1), &ambient_factor);
    addUniform(Uniform(program, "diffuse_color", GL_FLOAT, 1, 3, 1), glm::value_ptr(diffuse_color));
    addUniform(Uniform(program, "specular_color", GL_FLOAT, 1, 3, 1), glm::value_ptr(specular_color));
    addUniform(Uniform(program, "specular_exponent", GL_FLOAT, 1, 1, 1), &specular_exponent);
    addUniform(Uniform(program, "alpha", GL_FLOAT, 1, 1, 1), &alpha);
    addUniform(Uniform(program, "diffuse_map", GL_INT, 1, 1, 1), &diffuse_map_index);
    addUniform(Uniform(program, "diffuse_map_on", GL_INT, 1, 1, 1), &diffuse_map_on);
    addUniform(Uniform(program, "gloss_map", GL_INT, 1, 1, 1), &gloss_map_index);
    addUniform(Uniform(program, "gloss_map_on", GL_INT, 1, 1, 1), &gloss_map_on);
    addUniform(Uniform(program, "alpha_map", GL_INT, 1, 1, 1), &alpha_map_index);
    addUniform(Uniform(program, "alpha_map_on", GL_INT, 1, 1, 1), &alpha_map_on);
    addUniform(Uniform(program, "env_map", GL_INT, 1, 1, 1), &env_map_index);
    addUniform(Uniform(program, "env_map_factor", GL_FLOAT, 1, 1, 1), &env_map_factor);

    addVertexAttribute(renderer::VertexAttribute(program, "vertex", 3, GL_FLOAT, GL_FALSE));
    addVertexAttribute(renderer::VertexAttribute(program, "normal", 3, GL_FLOAT, GL_FALSE));
    addVertexAttribute(renderer::VertexAttribute(program, "color", 3, GL_FLOAT, GL_FALSE));
    addVertexAttribute(renderer::VertexAttribute(program, "uv", 2, GL_FLOAT, GL_FALSE));
}

void BasicMeshNodeTechnique::setAmbientFactor(float factor) {
    ambient_factor = factor;
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

void BasicMeshNodeTechnique::setAlpha(GLfloat a) {
    alpha = a;
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

void BasicMeshNodeTechnique::bindAlphaTexture(const model::Texture *texture) {
    glActiveTexture(GL_TEXTURE2); // activate the second texture
    alpha_map_on = texture == nullptr ? 0 : 1;
    bindTexture(texture);
}

void BasicMeshNodeTechnique::setEnvMapFactor(float factor) {
    env_map_factor = factor;
}

void BasicMeshNodeTechnique::setEnvMap(const model::Texture *texture) {
    env_map = texture;
}

void BasicMeshNodeTechnique::bindEnvMap() {
    glActiveTexture(GL_TEXTURE3); // activate the third texture
    bindCubeMap(env_map);
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

void BasicMeshNodeTechnique::bindCubeMap(const model::Texture *texture) {
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