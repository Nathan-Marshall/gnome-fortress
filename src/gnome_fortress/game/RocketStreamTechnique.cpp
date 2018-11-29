#include "gnome_fortress/game/RocketStreamTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace game {

RocketStreamTechnique::RocketStreamTechnique(
        GLuint program,
        const std::string &proj_name,
        const std::string &view_name,
        const std::string &model_name,
        const std::string &normal_name,
        const std::string &eye_pos_name,
        const std::string &timer_name,
        const std::string &power_name,
        const std::string &main_texture_name)
    : BasicProjectionTechnique(program, proj_name, view_name, model_name, normal_name, eye_pos_name),
      timer(0),
      power(1.0f),
      main_texture_index(0) {

    addUniform(renderer::Uniform(program, timer_name, GL_FLOAT, 1, 1, 1), &timer);
    addUniform(renderer::Uniform(program, power_name, GL_FLOAT, 1, 1, 1), &power);
    addUniform(renderer::Uniform(program, main_texture_name, GL_INT, 1, 1, 1), &main_texture_index);
}

void RocketStreamTechnique::setTimer(float time) {
    timer = time;
}

void RocketStreamTechnique::setPower(float p) {
    power = p;
}

void RocketStreamTechnique::bindMainTexture(const model::Texture *texture) {
    glActiveTexture(GL_TEXTURE0); // activate the first texture
    bindTexture(texture);
}

void RocketStreamTechnique::bindTexture(const model::Texture *texture) {
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

}
}