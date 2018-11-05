#pragma once

#include <vector>

#include <GL/glew.h>

namespace gnome_fortress {
namespace renderer {

class Uniform {
public:
    Uniform(GLuint shader_program,
            const std::string &name,
            GLenum type,
            GLsizei count,
            GLuint rows,
            GLuint columns);

    GLint getLocation() const;

    GLenum getType() const;

    GLsizei getCount() const;

    GLuint getRows() const;

    GLuint getColumns() const;

private:
    GLint location;
    GLenum type;
    GLsizei count;
    GLuint rows;
    GLuint columns;
};

}
}