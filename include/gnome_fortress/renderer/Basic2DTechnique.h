#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/renderer/Technique.h"

namespace gnome_fortress {
namespace renderer {

class Basic2DTechnique : public Technique {
public:
    Basic2DTechnique(GLuint program);

    // also sets the normal matrix to be the transposed inverse of the model matrix
    void setModelMatrix(const glm::mat3 &matrix);

private:
    glm::mat3 model_mat;
};

}
}