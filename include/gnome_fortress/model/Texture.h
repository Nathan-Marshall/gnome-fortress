#pragma once

#include <GL/glew.h>

namespace gnome_fortress {
namespace model {

struct Texture {
    // Creates a mesh with already-filled GL buffers
    Texture(GLuint id);

    // OpenGL texture ID
    GLuint id;
};

}
}