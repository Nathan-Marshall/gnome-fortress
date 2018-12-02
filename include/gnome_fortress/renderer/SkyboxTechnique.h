#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"
#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

namespace gnome_fortress {
namespace renderer {

class SkyboxTechnique : public BasicProjectionTechnique {
public:
    SkyboxTechnique(GLuint program);

    void bindSkyboxTexture(const model::Texture *texture);

private:
    GLint cube_map_index;
};

}
}