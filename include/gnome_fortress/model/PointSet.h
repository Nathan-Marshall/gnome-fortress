#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace gnome_fortress {
namespace model {

struct PointSet {
    PointSet();

    PointSet(
        const std::string &name,
        GLuint vbo,
        GLuint num_vertices,
        GLenum mode);

    // PointSet Name
    std::string name;

    // OpenGL vertex buffer object ID
    GLuint vbo;

    // number of vertices in the vbo
    GLuint num_vertices;

    // the mode to use for drawing (GL_LINES, GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLenum mode;
};

}
}