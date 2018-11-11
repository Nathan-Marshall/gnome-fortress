#include "gnome_fortress/model/Material.h"

namespace gnome_fortress {
namespace model {

Material::Material()
    : name(),
      Ka(),
      Kd(),
      Ks(),
      Ns(0),
      Ni(0),
      d(0),
      illum(0),
      map_Ka(nullptr),
      map_Kd(nullptr),
      map_Ks(nullptr),
      map_Ns(nullptr),
      map_d(nullptr),
      map_bump(nullptr) {

}

Material::Material(
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
        const Texture *map_bump)
    : name(name),
      Ka(Ka),
      Kd(Kd),
      Ks(Ks),
      Ns(Ns),
      Ni(Ni),
      d(d),
      illum(illum),
      map_Ka(map_Ka),
      map_Kd(map_Kd),
      map_Ks(map_Ks),
      map_Ns(map_Ns),
      map_d(map_d),
      map_bump(map_bump) {
}

}
}