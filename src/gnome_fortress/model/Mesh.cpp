#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace model {

Mesh::Mesh()
    : vbo(0),
      ebo(0),
      num_vertices(0),
      num_elements(0),
      mode(GL_TRIANGLES) {
}

Mesh::Mesh(
        const std::string &name,
        GLuint vbo,
        GLuint ebo,
        GLuint num_vertices,
        GLuint num_elements,
        GLenum mode,
        const Material *material)
    : name(name),
      vbo(vbo),
      ebo(ebo),
      num_vertices(num_vertices),
      num_elements(num_elements),
      mode(mode),
      material(material) {
}

}
}