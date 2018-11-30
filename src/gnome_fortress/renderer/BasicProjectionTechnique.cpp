#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

BasicProjectionTechnique::BasicProjectionTechnique(GLuint program)
    : Technique(program),
      projection_mat(),
      view_mat(),
      world_mat(),
      normal_mat(),
      eye_pos() {

    addUniform(Uniform(program, "projection_mat", GL_FLOAT, 1, 4, 4), glm::value_ptr(projection_mat));
    addUniform(Uniform(program, "view_mat", GL_FLOAT, 1, 4, 4), glm::value_ptr(view_mat));
    addUniform(Uniform(program, "world_mat", GL_FLOAT, 1, 4, 4), glm::value_ptr(world_mat));
    addUniform(Uniform(program, "normal_mat", GL_FLOAT, 1, 4, 4), glm::value_ptr(normal_mat));
    addUniform(Uniform(program, "eye_pos", GL_FLOAT, 1, 3, 1), glm::value_ptr(eye_pos));
}

void BasicProjectionTechnique::setProjectionMatrix(const glm::mat4 &matrix) {
    projection_mat = matrix;
}

void BasicProjectionTechnique::setViewMatrix(const glm::mat4 &matrix) {
    view_mat = matrix;
    eye_pos = glm::vec3(glm::inverse(matrix)[3]);
}

void BasicProjectionTechnique::setModelMatrix(const glm::mat4 &matrix) {
    world_mat = matrix;
    normal_mat = glm::transpose(glm::inverse(matrix));
}

}
}