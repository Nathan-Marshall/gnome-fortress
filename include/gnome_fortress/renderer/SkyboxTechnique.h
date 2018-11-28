#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"
#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

namespace gnome_fortress {
namespace renderer {

class SkyboxTechnique : public BasicProjectionTechnique {
public:
    SkyboxTechnique(
            GLuint program,
            const std::string &proj_name,
            const std::string &view_name,
            const std::string &model_name,
            const std::string &normal_name,
            const std::string &eye_pos_name,
            const std::string &cube_map_name);

    void bindSkyboxTexture(const model::Texture *texture);

private:
    GLint cube_map_index;
};

}
}