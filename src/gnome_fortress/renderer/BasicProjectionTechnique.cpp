#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

BasicProjectionTechnique::BasicProjectionTechnique(
        GLuint program,
        const std::string &proj_name,
        const std::string &view_name,
        const std::string &model_name,
        const std::string &normal_name,
        const std::string &eye_pos_name)
    : Technique(program),
      projection(),
      view(),
      model(),
      normal(),
      eye_pos() {

    addUniform(Uniform(program, proj_name, GL_FLOAT, 1, 4, 4), glm::value_ptr(projection));
    addUniform(Uniform(program, view_name, GL_FLOAT, 1, 4, 4), glm::value_ptr(view));
    addUniform(Uniform(program, model_name, GL_FLOAT, 1, 4, 4), glm::value_ptr(model));
    addUniform(Uniform(program, normal_name, GL_FLOAT, 1, 4, 4), glm::value_ptr(normal));
    addUniform(Uniform(program, eye_pos_name, GL_FLOAT, 1, 3, 1), glm::value_ptr(eye_pos));
}

void BasicProjectionTechnique::setProjectionMatrix(const glm::mat4 &matrix) {
    projection = matrix;
}

void BasicProjectionTechnique::setViewMatrix(const glm::mat4 &matrix) {
    view = matrix;
    eye_pos = glm::vec3(glm::inverse(matrix)[3]);
}

void BasicProjectionTechnique::setModelMatrix(const glm::mat4 &matrix) {
    model = matrix;
    normal = glm::transpose(glm::inverse(matrix));
}

}
}