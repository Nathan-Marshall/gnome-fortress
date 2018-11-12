#pragma once

#include <GL/glew.h>

#include <string>

namespace gnome_fortress {
namespace resource {

class ShaderProgramLoader {
public:
    /* Loads vertex and fragment shader programs from filename, with "_vp.glsl"/"_fp.glsl" added,
     * then compiles them and links them into a single GL shader program.
     */
    static GLuint LoadShaderProgram(const std::string &shader_prefix);

    // Deletes the OpenGL shader program
    static void UnloadShaderProgram(GLuint program);
};

}
}