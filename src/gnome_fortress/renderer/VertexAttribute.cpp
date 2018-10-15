#include "gnome_fortress/renderer/VertexAttribute.h"

#include <exception>

namespace gnome_fortress {
namespace renderer {

VertexAttribute::VertexAttribute(
        GLuint index,
        GLint component_count,
        GLenum type,
        GLboolean normalized)
    : index(index),
      component_count(component_count),
      type(type),
      normalized(normalized) {

    total_size = component_count * SizeOfGLType(type);
}

GLsizei VertexAttribute::SizeOfGLType(GLenum type) {
    if (type == GL_BYTE) {
        return sizeof(GLbyte);
    } else if (type == GL_UNSIGNED_BYTE) {
        return sizeof(GLubyte);
    } else if (type == GL_SHORT) {
        return sizeof(GLshort);
    } else if (type == GL_UNSIGNED_SHORT) {
        return sizeof(GLushort);
    } else if (type == GL_INT) {
        return sizeof(GLint);
    } else if (type == GL_UNSIGNED_INT) {
        return sizeof(GLuint);
    } else if (type == GL_HALF_FLOAT) {
        return sizeof(GLhalf);
    } else if (type == GL_FLOAT) {
        return sizeof(GLfloat);
    } else if (type == GL_DOUBLE) {
        return sizeof(GLdouble);
    } else if (type == GL_FIXED) {
        return sizeof(GLfixed);
    } else if (type == GL_INT_2_10_10_10_REV) {
        return sizeof(GLint);
    } else if (type == GL_UNSIGNED_INT_2_10_10_10_REV) {
        return sizeof(GLuint);
    } else if (type == GL_UNSIGNED_INT_10F_11F_11F_REV) {
        return sizeof(GLuint);
    } else {
        throw std::exception("Invalid GL type for VertexAttribute.");
        return 0;
    }
}

GLuint VertexAttribute::getIndex() const {
    return index;
}

GLint VertexAttribute::getComponentCount() const {
    return component_count;
}

GLenum VertexAttribute::getType() const {
    return type;
}

GLboolean VertexAttribute::isNormalized() const {
    return normalized;
}

GLsizei VertexAttribute::getTotalSize() const {
    return total_size;
}

}
}