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
            const std::string &diffuse_name);

    void bindDiffuseTexture(const model::Texture *texture);

private:
    GLint diffuse_texture_index;
};

}
}