#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/renderer/Technique.h"

namespace gnome_fortress {
namespace renderer {

class BasicProjectionTechnique : public Technique {
public:
    BasicProjectionTechnique(
            GLuint program,
            GLint proj_var_loc,
            GLint view_var_loc,
            GLint model_var_loc);

    void setProjectionMatrix(const glm::mat4 &matrix);

    void setViewMatrix(const glm::mat4 &matrix);

    void setModelMatrix(const glm::mat4 &matrix);

private:
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;
};

}
}