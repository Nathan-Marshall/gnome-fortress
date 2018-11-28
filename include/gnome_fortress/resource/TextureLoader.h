#pragma once

#include <string>

#include "gnome_fortress/model/Texture.h"

namespace gnome_fortress {
namespace resource {

class TextureLoader {
public:
    static model::Texture *LoadTexture(const std::string &filepath);

    static model::Texture *LoadSkyboxTexture(const std::string &filepath);

    static void UnloadTexture(model::Texture *texture);
};

}
}