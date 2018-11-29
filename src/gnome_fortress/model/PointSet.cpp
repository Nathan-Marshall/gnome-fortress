#include "gnome_fortress/model/PointSet.h"

namespace gnome_fortress {
namespace model {

PointSet::PointSet()
    : vbo(0),
      num_vertices(0),
      mode(GL_POINTS) {
}

PointSet::PointSet(
        const std::string &name,
        GLuint vbo,
        GLuint num_vertices,
        GLenum mode)
    : name(name),
      vbo(vbo),
      num_vertices(num_vertices),
      mode(mode) {
}

}
}