#include "gnome_fortress/resource/TextureLoader.h"

#include <SOIL/SOIL.h>

namespace gnome_fortress {
namespace resource {

model::Texture *TextureLoader::LoadTexture(const std::string &filepath) {
    GLuint id = SOIL_load_OGL_texture(filepath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (!id) {
        throw(std::ios_base::failure(std::string("Error loading texture ") + filepath + std::string(": ") + std::string(SOIL_last_result())));
    }
    return new model::Texture(id);
}

void TextureLoader::UnloadTexture(model::Texture *texture) {
    glDeleteTextures(1, &texture->id);
    delete texture;
}

}
}