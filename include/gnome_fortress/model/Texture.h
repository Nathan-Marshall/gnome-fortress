#pragma once

#include <GL/glew.h>

namespace gnome_fortress {
namespace model {

struct Texture {
    Texture();

    Texture(GLuint id);

    // OpenGL texture ID
    GLuint id;
};

}
}