#include "gnome_fortress/renderer/Uniform.h"

#include <exception>

namespace gnome_fortress {
namespace renderer {

Uniform::Uniform(
        GLint location,
        GLenum type,
        GLsizei count,
        GLuint rows,
        GLuint columns)
    : location(location),
      type(type),
      count(count),
      rows(rows),
      columns(columns) {
    if (rows > 4) {
        throw std::exception("Too many rows for Uniform. Maximum is 4.");
    }
    if (columns > 4) {
        throw std::exception("Too many columns for Uniform. Maximum is 4.");
    }
    if (type != GL_FLOAT && rows > 1 && columns > 1) {
        throw std::exception("Only a uniform with float values can be a matrix. Set either rows or columns equal to 1.");
    }
}

GLint Uniform::getLocation() const {
    return location;
}

GLenum Uniform::getType() const {
    return type;
}

GLsizei Uniform::getCount() const {
    return count;
}

GLuint Uniform::getRows() const {
    return rows;
}

GLuint Uniform::getColumns() const {
    return columns;
}

}
}