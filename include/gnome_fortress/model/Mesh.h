#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "gnome_fortress/model/Material.h"

namespace gnome_fortress {
namespace model {

struct Mesh {
    Mesh();

    Mesh(const std::string &name,
        GLuint vbo,
        GLuint ebo,
        GLuint num_vertices,
        GLuint num_elements,
        GLenum mode,
        const Material *material);

    // Mesh Name
    std::string name;

    // OpenGL vertex buffer object ID
    GLuint vbo;

    // OpenGL element buffer object ID (this will be 0 if the ebo is not being used)
    GLuint ebo;

    // number of vertices in the vbo
    GLuint num_vertices;

    // number of elements in the ebo
    GLuint num_elements;

    // the mode to use for drawing (GL_LINES, GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLenum mode;

    // material properties
    const Material *material;
};

}
}