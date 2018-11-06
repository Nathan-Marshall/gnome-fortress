#pragma once

#include <string>

#include <GL/glew.h>

namespace gnome_fortress {
namespace renderer {

class VertexAttribute {
public:
    VertexAttribute(
            GLuint shader_program,
            const std::string &name,
            GLint component_count,
            GLenum type,
            GLboolean normalized);

    static GLsizei SizeOfGLType(GLenum type);

    GLint getIndex() const;

    GLint getComponentCount() const;

    GLenum getType() const;

    GLboolean isNormalized() const;

    GLsizei getTotalSize() const;

private:
    GLint index;
    GLint component_count;
    GLenum type;
    GLboolean normalized;

    // size computed from component_count and type
    GLsizei total_size;
};

}
}