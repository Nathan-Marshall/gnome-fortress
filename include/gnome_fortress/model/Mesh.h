#pragma once

#include <GL/glew.h>

namespace gnome_fortress {
namespace model {

struct Mesh {
    // Creates a mesh with already-filled GL buffers
    Mesh(GLuint vbo, GLuint ebo, GLuint num_vertices, GLuint num_elements, GLenum mode);

    // Generates GL buffers and stores the given vertices and elements in them
    Mesh::Mesh(const GLvoid *vertices, GLsizei verticesSize, GLsizei singleVertexSize, GLuint *elements, GLsizei elementsSize, GLenum mode);

    // OpenGL vertex buffer object ID
    GLuint vbo;

    // OpenGL element buffer object ID (this will be 0 if the ebo is not being used)
    GLuint ebo;

    // number of vertices
    GLuint num_vertices;

    // number of elements in the ebo
    GLuint num_elements;

    // the mode to use for drawing (GL_LINES, GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLenum mode;
};

}
}