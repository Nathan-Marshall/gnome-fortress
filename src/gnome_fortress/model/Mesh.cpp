#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace model {

Mesh::Mesh()
    : vbo(0),
      num_vertices(0),
      ebo(0),
      num_elements(0),
      mode(GL_TRIANGLES) {

}

Mesh::Mesh(GLvoid *vertices, GLsizei verticesSize, GLsizei singleVertexSize, GLuint *elements, GLsizei elementsSize, GLenum mode)
    : vbo(0),
      num_vertices(verticesSize/singleVertexSize),
      ebo(0),
      num_elements(elementsSize/sizeof(GLuint)),
      mode(mode) {

    // Create OpenGL vertex buffer for mesh
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // Create OpenGL element buffer for mesh
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsSize, elements, GL_STATIC_DRAW);
}

}
}