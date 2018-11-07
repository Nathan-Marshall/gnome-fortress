#pragma once

#include <GL/glew.h>

#include <string>

namespace gnome_fortress {
namespace shader {

/* Loads vertex and fragment shader programs from filename, with "_vp.glsl"/"_fp.glsl" added,
 * then compiles them and links them into a single GL shader program.
 */
GLuint CreateShaderProgram(const std::string &shader_prefix);

std::string LoadTextFile(const std::string &filename);

}
}