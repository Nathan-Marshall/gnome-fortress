#pragma once

#include <string>

#include "gnome_fortress/model/MeshGroup.h"

namespace gnome_fortress {
namespace resource {

class ResourceManager;

class MeshGroupLoader {
public:
    static model::MeshGroup *LoadMeshGroup(const std::string &filename, resource::ResourceManager &resourceManager);

    static void UnloadMeshGroup(model::MeshGroup *meshGroup);

private:
    static std::string GetRelativePathFromAbsolutePath(const std::string &filename, resource::ResourceManager &resourceManager);
};

}
}