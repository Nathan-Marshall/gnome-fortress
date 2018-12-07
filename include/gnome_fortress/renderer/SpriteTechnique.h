#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"
#include "gnome_fortress/renderer/Basic2DTechnique.h"

namespace gnome_fortress {
namespace renderer {

class SpriteTechnique : public Basic2DTechnique {
public:
    SpriteTechnique(GLuint program);

    void bindMainTexture(const model::Texture *texture);

protected:
    void bindTexture(const model::Texture *texture);

private:
    GLint main_texture_index;
};

}
}