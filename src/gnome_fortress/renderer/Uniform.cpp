#include "gnome_fortress/renderer/Uniform.h"

#include <exception>
#include <iostream>

namespace gnome_fortress {
namespace renderer {

Uniform::Uniform(
        GLuint shader_program,
        const std::string &name,
        GLenum type,
        GLsizei count,
        GLuint rows,
        GLuint columns)
    : type(type),
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

    location = glGetUniformLocation(shader_program, name.c_str());
    if (location < 0) {
        std::cerr << "Failed to find uniform \"" << name.c_str() << "\" in shader program." << std::endl;
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