#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace model {

Mesh::Mesh(GLuint vbo, GLuint ebo, GLuint num_vertices, GLuint num_elements, GLenum mode)
    : vbo(vbo),
      ebo(ebo),
      num_vertices(num_vertices),
      num_elements(num_elements),
      mode(mode) {
}

}
}