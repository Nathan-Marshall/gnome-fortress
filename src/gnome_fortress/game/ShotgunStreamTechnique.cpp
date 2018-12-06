#include "gnome_fortress/game/ShotgunStreamTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace game {

    ShotgunStreamTechnique::ShotgunStreamTechnique(GLuint program)
    : BasicProjectionTechnique(program),
      timer(0),
      power(1.0f),
      main_texture_index(0) {

    addUniform(renderer::Uniform(program, "timer", GL_FLOAT, 1, 1, 1), &timer);
    addUniform(renderer::Uniform(program, "power", GL_FLOAT, 1, 1, 1), &power);
    addUniform(renderer::Uniform(program, "main_texture", GL_INT, 1, 1, 1), &main_texture_index);

    addVertexAttribute(renderer::VertexAttribute(program, "vertex", 3, GL_FLOAT, GL_FALSE));
    addVertexAttribute(renderer::VertexAttribute(program, "normal", 3, GL_FLOAT, GL_FALSE));
    addVertexAttribute(renderer::VertexAttribute(program, "color", 3, GL_FLOAT, GL_FALSE));
}

void ShotgunStreamTechnique::setTimer(float time) {
    timer = time;
}

void ShotgunStreamTechnique::setPower(float p) {
    power = p;
}

void ShotgunStreamTechnique::bindMainTexture(const model::Texture *texture) {
    glActiveTexture(GL_TEXTURE0); // activate the first texture
    bindTexture(texture);
}

void ShotgunStreamTechnique::bindTexture(const model::Texture *texture) {
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