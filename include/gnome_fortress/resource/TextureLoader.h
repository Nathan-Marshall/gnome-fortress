#pragma once

#include <string>

#include "gnome_fortress/model/Texture.h"

namespace gnome_fortress {
namespace resource {

class TextureLoader {
public:
    //Load a texture
    static model::Texture *LoadTexture(const std::string &filepath);

    //Load the skybox into a texture
    static model::Texture *LoadSkyboxTexture(const std::string &filepath);

    static void UnloadTexture(model::Texture *texture);
};

}
}