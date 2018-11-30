#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/renderer/Technique.h"

namespace gnome_fortress {
namespace renderer {

class BasicProjectionTechnique : public Technique {
public:
    BasicProjectionTechnique(GLuint program);

    void setProjectionMatrix(const glm::mat4 &matrix);

    void setViewMatrix(const glm::mat4 &matrix);

    // also sets the normal matrix to be the transposed inverse of the model matrix
    void setModelMatrix(const glm::mat4 &matrix);

private:
    glm::mat4 projection_mat;
    glm::mat4 view_mat;
    glm::mat4 world_mat;
    glm::mat4 normal_mat;
    glm::vec3 eye_pos;
};

}
}