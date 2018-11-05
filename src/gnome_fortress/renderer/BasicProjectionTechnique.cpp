#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

BasicProjectionTechnique::BasicProjectionTechnique(
        GLuint program,
        const std::string &proj_name,
        const std::string &view_name,
        const std::string &model_name)
    : Technique(program),
      projection(),
      view(),
      model() {

    addUniform(Uniform(program, proj_name, GL_FLOAT, 1, 4, 4), glm::value_ptr(projection));
    addUniform(Uniform(program, view_name, GL_FLOAT, 1, 4, 4), glm::value_ptr(view));
    addUniform(Uniform(program, model_name, GL_FLOAT, 1, 4, 4), glm::value_ptr(model));
}

void BasicProjectionTechnique::setProjectionMatrix(const glm::mat4 &matrix) {
    projection = matrix;
}

void BasicProjectionTechnique::setViewMatrix(const glm::mat4 &matrix) {
    view = matrix;
}

void BasicProjectionTechnique::setModelMatrix(const glm::mat4 &matrix) {
    model = matrix;
}

}
}