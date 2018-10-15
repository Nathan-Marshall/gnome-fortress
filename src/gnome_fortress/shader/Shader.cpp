/*
 * Copyright (c) 2018 Nathan Marshall <Nathagnome_fortress@cmail.carleton.ca>,
 * Oliver van Kaick <Oliver.vanKaick@carleton.ca>, David Mould <mould@scs.carleton.ca>
 */

#include "gnome_fortress/shader/Shader.h"

#include <iostream>

namespace gnome_fortress {
namespace shader {

// Compiles and links a vertex shader and fragment shader from the given source code.
GLuint CreateShaderProgram(const char *vertex_shader_source, const char *fragment_shader_source) {
    // Create a shader from vertex program source code
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader_source, NULL);
    glCompileShader(vs);

    // Check if shader compiled successfully
    GLint status;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(vs, 512, NULL, buffer);
        throw(std::ios_base::failure(std::string("Error compiling vertex shader: ") + std::string(buffer)));
    }

    // Create a shader from the fragment program source code
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader_source, NULL);
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
    glDeleteShader(fs);

    return program;
}

}
}