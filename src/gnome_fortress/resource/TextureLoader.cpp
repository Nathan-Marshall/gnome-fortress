#include "gnome_fortress/resource/TextureLoader.h"

#include <SOIL/SOIL.h>

namespace gnome_fortress {
namespace resource {

//Load a texture from the given filepath using soil
model::Texture *TextureLoader::LoadTexture(const std::string &filepath) {
    GLuint id = SOIL_load_OGL_texture(filepath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (!id) {
        throw(std::ios_base::failure(std::string("Error loading texture ") + filepath + std::string(": ") + std::string(SOIL_last_result())));
    }
    return new model::Texture(id);
}

model::Texture *TextureLoader::LoadSkyboxTexture(const std::string &filepath) {
    // Get base and extension of filename
    std::string fn(filepath);
    int pos = fn.find(".");
    std::string base = fn.substr(0, pos);
    std::string ext = fn.substr(pos + 1);

    // Create filenames of each individual cube face
    std::string fn_xn = base + "_xn." + ext;
    std::string fn_xp = base + "_xp." + ext;
    std::string fn_yn = base + "_yn." + ext;
    std::string fn_yp = base + "_yp." + ext;
    std::string fn_zn = base + "_zn." + ext;
    std::string fn_zp = base + "_zp." + ext;

    // Load cube map from file
    GLuint id = SOIL_load_OGL_cubemap(fn_xp.c_str(), fn_xn.c_str(), fn_yp.c_str(), fn_yn.c_str(), fn_zp.c_str(), fn_zn.c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0/*SOIL_FLAG_INVERT_Y*/);
    if (!id) {
        throw(std::ios_base::failure(std::string("Error loading cube map ") + std::string(base) + std::string("<spec>.") + std::string(ext) + std::string(": ") + std::string(SOIL_last_result())));
    }
    return new model::Texture(id);
}

//Delete the texture
void TextureLoader::UnloadTexture(model::Texture *texture) {
    glDeleteTextures(1, &texture->id);
    delete texture;
}

}
}