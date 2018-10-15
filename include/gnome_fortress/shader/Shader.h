#pragma once

#include <GL/glew.h>

namespace gnome_fortress {
namespace shader {

GLuint CreateShaderProgram(const char *vertex_shader_source, const char *fragment_shader_source);

}
}