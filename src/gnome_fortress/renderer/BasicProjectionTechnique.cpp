#include "gnome_fortress/renderer/BasicProjectionTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

BasicProjectionTechnique::BasicProjectionTechnique(
        GLuint program,
        GLint proj_var_loc,
        GLint view_var_loc,
        GLint model_var_loc)
    : Technique(program),
      projection(),
      view(),
      model() {

    addUniform(Uniform(proj_var_loc, GL_FLOAT, 1, 4, 4), glm::value_ptr(projection));
    addUniform(Uniform(view_var_loc, GL_FLOAT, 1, 4, 4), glm::value_ptr(view));
    addUniform(Uniform(model_var_loc, GL_FLOAT, 1, 4, 4), glm::value_ptr(model));
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