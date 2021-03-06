#include <gnome_fortress/resource/ResourceManager.h>

#include "gnome_fortress/resource/MeshGroupLoader.h"
#include "gnome_fortress/resource/ShaderProgramLoader.h"
#include "gnome_fortress/resource/TextureLoader.h"

namespace gnome_fortress {
namespace resource {

ResourceManager::ResourceManager(const std::string &inResourcesDirectory)
    : resourcesDirectory(inResourcesDirectory),
      meshGroups(),
      shaderPrograms(),
      textures() {
    if (resourcesDirectory.back() != '/') {
        resourcesDirectory.append("/");
    }
}

ResourceManager::~ResourceManager() {
    unloadAll();
}

std::string ResourceManager::getResourcesDirectory() const {
    return resourcesDirectory;
}

/*Methods used for loading and unloading resources of various types.
  getOrLoad can be used to use already loaded resources, or load them 
  if they haven't been loaded already. All resources get unloaded
  automatically upon destruction.*/


void ResourceManager::loadMeshGroup(const std::string &relativePath) {
    std::string fullPath = resourcesDirectory + relativePath;
    meshGroups[relativePath] = MeshGroupLoader::LoadMeshGroup(fullPath, *this);
}
model::MeshGroup *ResourceManager::getOrLoadMeshGroup(const std::string &relativePath) {
    if (meshGroups.find(relativePath) == meshGroups.end()) {
        loadMeshGroup(relativePath);
    }
    return meshGroups[relativePath];
}
void ResourceManager::unloadMeshGroup(const std::string &relativePath) {
    MeshGroupLoader::UnloadMeshGroup(meshGroups[relativePath]);
    meshGroups.erase(relativePath);
}

void ResourceManager::loadShaderProgram(const std::string &relativePath) {
    std::string fullPath = resourcesDirectory + relativePath;
    shaderPrograms[relativePath] = ShaderProgramLoader::LoadShaderProgram(fullPath);
}
GLuint ResourceManager::getOrLoadShaderProgram(const std::string &relativePath) {
    if (shaderPrograms.find(relativePath) == shaderPrograms.end()) {
        loadShaderProgram(relativePath);
    }
    return shaderPrograms[relativePath];
}
void ResourceManager::unloadShaderProgram(const std::string &relativePath) {
    ShaderProgramLoader::UnloadShaderProgram(shaderPrograms[relativePath]);
    shaderPrograms.erase(relativePath);
}

void ResourceManager::loadAudioClip(const std::string &relativePath) {
    std::string fullPath = resourcesDirectory + relativePath;
    audioClips[relativePath] = fullPath;
}
const char* ResourceManager::getOrLoadAudioClip(const std::string &relativePath) {
    if (audioClips.find(relativePath) == audioClips.end()) {
        loadAudioClip(relativePath);
    }
    return audioClips[relativePath].c_str();
}

void ResourceManager::unloadAudioClip(const std::string &relativePath) {
    audioClips.erase(relativePath);
}

void ResourceManager::loadTexture(const std::string &relativePath) {
    std::string fullPath = resourcesDirectory + relativePath;
    textures[relativePath] = TextureLoader::LoadTexture(fullPath);
}
model::Texture *ResourceManager::getOrLoadTexture(const std::string &relativePath) {
    if (textures.find(relativePath) == textures.end()) {
        loadTexture(relativePath);
    }
    return textures[relativePath];
}
void ResourceManager::loadSkyboxTexture(const std::string &relativePath) {
    std::string fullPath = resourcesDirectory + relativePath;
    textures[relativePath] = TextureLoader::LoadSkyboxTexture(fullPath);
}
model::Texture *ResourceManager::getOrLoadSkyboxTexture(const std::string &relativePath) {
    if (textures.find(relativePath) == textures.end()) {
        loadSkyboxTexture(relativePath);
    }
    return textures[relativePath];
}
void ResourceManager::unloadTexture(const std::string &relativePath) {
    TextureLoader::UnloadTexture(textures[relativePath]);
    textures.erase(relativePath);
}

//Unload all currently loaded resources
void ResourceManager::unloadAll() {
    while (!meshGroups.empty()) {
        unloadMeshGroup(meshGroups.begin()->first);
    }
    while (!shaderPrograms.empty()) {
        unloadShaderProgram(shaderPrograms.begin()->first);
    }
    while (!textures.empty()) {
        unloadTexture(textures.begin()->first);
    }
    while (!audioClips.empty()) {
        unloadAudioClip(audioClips.begin()->first);
    }
}

}
}