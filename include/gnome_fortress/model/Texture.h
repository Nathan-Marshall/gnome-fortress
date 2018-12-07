#pragma once

#include <GL/glew.h>

namespace gnome_fortress {
namespace model {

struct Texture {
    Texture();

    //The int value for the texture
    Texture(GLuint id);

    // OpenGL texture ID
    GLuint id;
};

}
}