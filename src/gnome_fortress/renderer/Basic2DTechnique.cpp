#include "gnome_fortress/renderer/Basic2DTechnique.h"

#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace renderer {

Basic2DTechnique::Basic2DTechnique(GLuint program)
    : Technique(program),
      model_mat(){

    addUniform(Uniform(program, "model_mat", GL_FLOAT, 1, 3, 3), glm::value_ptr(model_mat));
}

void Basic2DTechnique::setModelMatrix(const glm::mat3 &matrix) {
    model_mat = matrix;
}

}
}