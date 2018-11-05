#pragma once

#include <string>

#include <GL/glew.h>

namespace gnome_fortress {
namespace model {

struct Texture {
    // Creates a mesh with already-filled GL buffers
    Texture(GLuint id);

    // Loads texture from filename, relative to resources directory
    Texture::Texture(const std::string &partial_filename);

    // OpenGL texture ID
    GLuint id;
};

}
}