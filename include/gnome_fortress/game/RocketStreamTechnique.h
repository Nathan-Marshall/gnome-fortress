#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"
#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

namespace gnome_fortress {
namespace game {

class RocketStreamTechnique : public renderer::BasicProjectionTechnique {
public:
    RocketStreamTechnique(GLuint program);

    void setTimer(float time);

    void setPower(float power);

    void bindMainTexture(const model::Texture *texture);

protected:
    void bindTexture(const model::Texture *texture);

private:
    GLfloat timer;
    GLfloat power;
    GLint main_texture_index;
};

}
}