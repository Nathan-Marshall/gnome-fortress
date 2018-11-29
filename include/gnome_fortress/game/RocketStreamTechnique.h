#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"
#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

namespace gnome_fortress {
namespace game {

class RocketStreamTechnique : public renderer::BasicProjectionTechnique {
public:
    RocketStreamTechnique(
        GLuint program,
        const std::string &proj_name,
        const std::string &view_name,
        const std::string &model_name,
        const std::string &normal_name,
        const std::string &eye_pos_name,
        const std::string &timer_name,
        const std::string &power_name,
        const std::string &main_texture_name);

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