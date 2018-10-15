#pragma once

#include <vector>

#include "gnome_fortress/renderer/Uniform.h"
#include "gnome_fortress/renderer/VertexAttribute.h"

namespace gnome_fortress {
namespace renderer {

class Technique {
public:
    struct UniformEntry {
        UniformEntry(const Uniform &uni, const GLfloat *fvalues);
        UniformEntry(const Uniform &uni, const GLint *ivalues);
        UniformEntry(const Uniform &uni, const GLuint *uivalues);

        Uniform uni;

        // a UniformEntry will only use one of the following pointers
        const GLfloat *fvalues;
        const GLint *ivalues;
        const GLuint *uivalues;
    };

    struct AttributeEntry {
        AttributeEntry(const VertexAttribute &attr, GLvoid *offset);

        VertexAttribute attr;
        GLvoid *offset;
    };

    Technique(GLuint program);

    GLuint getShader() const;

    void addUniform(const Uniform &uni, const GLfloat *fvalues);

    void addUniform(const Uniform &uni, const GLint *ivalues);

    void addUniform(const Uniform &uni, const GLuint *uivalues);

    void addVertexAttribute(const VertexAttribute &attr);

    void activate() const;

    void deactivate() const;

private:
    GLuint shader_program;
    std::vector<UniformEntry> uniforms;
    std::vector<AttributeEntry> attributes;
    GLsizei stride;
};

}
}