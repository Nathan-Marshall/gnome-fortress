#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"
#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

namespace gnome_fortress {
namespace game {

class PurpleRocketStreamTechnique : public renderer::BasicProjectionTechnique {
public:
    PurpleRocketStreamTechnique(GLuint program);

    //Set the timer
    void setTimer(float time);

    //Set the power of the rocket stream
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