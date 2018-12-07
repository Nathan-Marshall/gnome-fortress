#pragma once

#include <string>

#include "gnome_fortress/model/MeshGroup.h"

namespace gnome_fortress {
namespace resource {

class ResourceManager;

class MeshGroupLoader {
public:
    //Load a new mesh ground from a file
    static model::MeshGroup *LoadMeshGroup(const std::string &filename, resource::ResourceManager &resourceManager);

    //Unload a mesh group
    static void UnloadMeshGroup(model::MeshGroup *meshGroup);

private:
    //Get the relative file path for the resource 
    static std::string GetRelativePathFromAbsolutePath(const std::string &filename, resource::ResourceManager &resourceManager);
};

}
}