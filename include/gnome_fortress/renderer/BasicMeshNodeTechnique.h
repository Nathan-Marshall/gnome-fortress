#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"
#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

namespace gnome_fortress {
namespace renderer {

class BasicMeshNodeTechnique : public BasicProjectionTechnique {
public:
    BasicMeshNodeTechnique(GLuint program);

    void setAmbientFactor(float factor);
    void setDiffuseColor(const glm::vec3 &color);
    void setSpecularColor(const glm::vec3 &color);
    void setSpecularExponent(GLfloat exponent);
    void setAlpha(GLfloat alpha);

    void setTint(const glm::vec4 &color);

    void bindDiffuseTexture(const model::Texture *texture);
    void bindGlossTexture(const model::Texture *texture);
    void bindAlphaTexture(const model::Texture *texture);

    void setEnvMapFactor(float factor);
    void setEnvMap(const model::Texture *texture);
    void bindEnvMap();

protected:
    void bindTexture(const model::Texture *texture);
    void bindCubeMap(const model::Texture *texture);

private:
    GLfloat ambient_factor;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    GLfloat specular_exponent;
    GLfloat alpha;

    glm::vec4 tint;

    GLint diffuse_map_index;
    GLint diffuse_map_on;
    GLint gloss_map_index;
    GLint gloss_map_on;
    GLint alpha_map_index;
    GLint alpha_map_on;

    const model::Texture *env_map;
    GLint env_map_index;
    GLfloat env_map_factor;
};

}
}