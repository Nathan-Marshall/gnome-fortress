#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "gnome_fortress/model/Texture.h"

namespace gnome_fortress {
namespace model {

struct Material {
    Material();

    Material(
        const std::string &name,
        const glm::vec3 &Ka,
        const glm::vec3 &Kd,
        const glm::vec3 &Ks,
        float Ns,
        float Ni,
        float d,
        int illum,
        const Texture *map_Ka,
        const Texture *map_Kd,
        const Texture *map_Ks,
        const Texture *map_Ns,
        const Texture *map_d,
        const Texture *map_bump);

    // Material Name
    std::string name;
    // Ambient Color
    glm::vec3 Ka;
    // Diffuse Color
    glm::vec3 Kd;
    // Specular Color
    glm::vec3 Ks;
    // Specular Exponent
    float Ns;
    // Optical Density
    float Ni;
    // Dissolve
    float d;
    // Illumination
    int illum;
    // Ambient Texture Map
    const Texture *map_Ka;
    // Diffuse Texture Map
    const Texture *map_Kd;
    // Specular Texture Map
    const Texture *map_Ks;
    // Specular Hightlight Map
    const Texture *map_Ns;
    // Alpha Texture Map
    const Texture *map_d;
    // Bump Map
    const Texture *map_bump;
};

}
}