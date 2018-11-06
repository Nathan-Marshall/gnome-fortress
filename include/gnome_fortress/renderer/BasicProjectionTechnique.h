#pragma once

#include <glm/glm.hpp>

#include "gnome_fortress/renderer/Technique.h"

namespace gnome_fortress {
namespace renderer {

class BasicProjectionTechnique : public Technique {
public:
    BasicProjectionTechnique(
            GLuint program,
            const std::string &proj_name,
            const std::string &view_name,
            const std::string &model_name);

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