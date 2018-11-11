#include <gnome_fortress/resource/ResourceManager.h>

#include <SOIL/SOIL.h>

#include "gnome_fortress/model/OBJParser.h"
#include "gnome_fortress/shader/Shader.h"

namespace gnome_fortress {
namespace resource {

ResourceManager::ResourceManager(const std::string &inResourcesDirectory)
    : resourcesDirectory(inResourcesDirectory),
      meshes(),
      shaderPrograms(),
      textures() {
    if (resourcesDirectory.back() != '/') {
        resourcesDirectory.append("/");
    }
}
ResourceManager::~ResourceManager() {
    unloadAll();
}

void ResourceManager::loadMesh(const std::string &relativePath) {
    std::string fullPath = resourcesDirectory + relativePath;
    model::Mesh *mesh = new model::Mesh(model::LoadMesh(fullPath));
    meshes[relativePath] = mesh;
}
model::Mesh *ResourceManager::getOrLoadMesh(const std::string &relativePath) {
    if (meshes.find(relativePath) == meshes.end()) {
        loadMesh(relativePath);
    }
    return meshes[relativePath];
}
void ResourceManager::unloadMesh(const std::string &relativePath) {
    model::Mesh *mesh = meshes[relativePath];
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteBuffers(1, &mesh->ebo);
    delete mesh;
    meshes.erase(relativePath);
}

void ResourceManager::loadShaderProgram(const std::string &relativePath) {
    std::string fullPath = resourcesDirectory + relativePath;
    GLuint id = shader::CreateShaderProgram(fullPath);
    shaderPrograms[relativePath] = id;
}
GLuint ResourceManager::getOrLoadShaderProgram(const std::string &relativePath) {
    if (shaderPrograms.find(relativePath) == shaderPrograms.end()) {
        loadShaderProgram(relativePath);
    }
    return shaderPrograms[relativePath];
}
void ResourceManager::unloadShaderProgram(const std::string &relativePath) {
    GLuint shaderProgram = shaderPrograms[relativePath];
    glDeleteProgram(shaderProgram);
    shaderPrograms.erase(relativePath);
}

void ResourceManager::loadTexture(const std::string &relativePath) {
    std::string fullPath = resourcesDirectory + relativePath;
    GLuint id = SOIL_load_OGL_texture(fullPath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (!id) {
        throw(std::ios_base::failure(std::string("Error loading texture ") + fullPath + std::string(": ") + std::string(SOIL_last_result())));
    }
    textures[relativePath] = new model::Texture(id);
}
model::Texture *ResourceManager::getOrLoadTexture(const std::string &relativePath) {
    if (textures.find(relativePath) == textures.end()) {
        loadTexture(relativePath);
    }
    return textures[relativePath];
}
void ResourceManager::unloadTexture(const std::string &relativePath) {
    model::Texture *texture = textures[relativePath];
    glDeleteTextures(1, &texture->id);
    delete texture;
    textures.erase(relativePath);
}

void ResourceManager::unloadAll() {
    while (!meshes.empty()) {
        unloadMesh(meshes.begin()->first);
    }
    while (!shaderPrograms.empty()) {
        unloadShaderProgram(shaderPrograms.begin()->first);
    }
    while (!textures.empty()) {
        unloadTexture(textures.begin()->first);
    }
}

}
}