#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"
#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

namespace gnome_fortress {
namespace renderer {

class BasicMeshNodeTechnique : public BasicProjectionTechnique {
public:
    BasicMeshNodeTechnique(
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
            const std::string &gloss_map_on_name);

    void setDiffuseColor(const glm::vec3 &color);
    void setSpecularColor(const glm::vec3 &color);
    void setSpecularExponent(GLfloat exponent);

    void bindDiffuseTexture(const model::Texture *texture);
    void bindGlossTexture(const model::Texture *texture);

protected:
    void bindTexture(const model::Texture *texture);

private:
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    GLfloat specular_exponent;

    GLint diffuse_map_index;
    GLint diffuse_map_on;
    GLint gloss_map_index;
    GLint gloss_map_on;
};

}
}