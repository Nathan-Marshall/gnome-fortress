/*
 * Copyright (c) 2018 Nathan Marshall <NathanMarshall@cmail.carleton.ca>, Mitchell Blanchard <MiitchellBlanchard@cmail.carleton.ca>, Megan Perera <MeganPerera@cmail.carleton.ca>,
 * Oliver van Kaick <Oliver.vanKaick@carleton.ca>, David Mould <mould@scs.carleton.ca>
 */

#include "gnome_fortress/resource/ShaderProgramLoader.h"

#include "gnome_fortress/resource/FileReader.h"

namespace gnome_fortress {
namespace resource {

GLuint ShaderProgramLoader::LoadShaderProgram(const std::string &shader_prefix) {
    std::string vp_source_str = ReadTextFile(shader_prefix + "_vp.glsl");
    const GLchar *vp_source = vp_source_str.c_str();
    
    std::string gp_source_str = "";
    const GLchar *gp_source = nullptr;
    try {
        gp_source_str = ReadTextFile(shader_prefix + "_gp.glsl");
        gp_source = gp_source_str.c_str();
    } catch (std::ios_base::failure ex) {
        // no geometry shader
    }

    std::string fp_source_str = ReadTextFile(shader_prefix + "_fp.glsl");
    const GLchar *fp_source = fp_source_str.c_str();

    // Create a shader from vertex program source code
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vp_source, NULL);
    glCompileShader(vs);

    // Check if shader compiled successfully
    GLint status;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(vs, 512, NULL, buffer);
        throw(std::ios_base::failure(std::string("Error compiling vertex shader: ") + std::string(buffer)));
    }

    GLuint gs = 0;
    if (gp_source) {
        // Create a shader from the geometry program source code
        gs = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gs, 1, &gp_source, NULL);
        glCompileShader(gs);

        // Check if shader compiled successfully
        GLint status;
        glGetShaderiv(gs, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            char buffer[512];
            glGetShaderInfoLog(gs, 512, NULL, buffer);
            throw(std::ios_base::failure(std::string("Error compiling geometry shader: ") + std::string(buffer)));
        }
    }

    // Create a shader from the fragment program source code
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fp_source, NULL);
    glCompileShader(fs);

    // Check if shader compiled successfully
    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(fs, 512, NULL, buffer);
        throw(std::ios_base::failure(std::string("Error compiling fragment shader: ") + std::string(buffer)));
    }

    // Create a shader program linking both vertex and fragment shaders
    // together
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    if (gs) {
        glAttachShader(program, gs);
    }
    glAttachShader(program, fs);
    glLinkProgram(program);

    // Check if shaders were linked successfully
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(program, 512, NULL, buffer);
        throw(std::ios_base::failure(std::string("Error linking shaders: ") + std::string(buffer)));
    }

    // Delete memory used by shaders, since they were already compiled and linked
    glDeleteShader(vs);
    if (gs) {
        glDeleteShader(gs);
    }
    glDeleteShader(fs);

    return program;
}

void ShaderProgramLoader::UnloadShaderProgram(GLuint program) {
    glDeleteProgram(program);
}

}
}