#include "gnome_fortress/model/Texture.h"

#include <SOIL/SOIL.h>

#include "resources_config.h"

namespace gnome_fortress {
namespace model {

Texture::Texture(GLuint id)
    : id(id) {
}

Texture::Texture(const std::string &partial_filename)
    : id(0) {

    std::string filename = std::string(RESOURCES_DIRECTORY) + partial_filename;
    id = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
    if (!id) {
        throw(std::ios_base::failure(std::string("Error loading texture ") + std::string(filename) + std::string(": ") + std::string(SOIL_last_result())));
    }
}

}
}