#pragma once

#include <string>
#include <unordered_map>

#include <gnome_fortress/model/Mesh.h>
#include <gnome_fortress/model/Texture.h>

namespace gnome_fortress {
namespace resource {

class ResourceManager {
public:
    ResourceManager(const std::string &resourcesDirectory);
    ~ResourceManager();

    void loadMesh(const std::string &relativePath);
    model::Mesh *getOrLoadMesh(const std::string &relativePath);
    void unloadMesh(const std::string &relativePath);

    /* When dealing with shaders, ResourceManager expects a filename prefix, which refers to both the vertex and
     * fragment shader source files. "_vp.glsl" is appended for the vertex shader and /"_fp.glsl" is appended for the
     * fragment shader.*/
    void loadShaderProgram(const std::string &relativePath);
    /* When dealing with shaders, ResourceManager expects a filename prefix, which refers to both the vertex and
     * fragment shader source files. "_vp.glsl" is appended for the vertex shader and /"_fp.glsl" is appended for the
     * fragment shader.*/
    GLuint getOrLoadShaderProgram(const std::string &relativePath);
    /* When dealing with shaders, ResourceManager expects a filename prefix, which refers to both the vertex and
     * fragment shader source files. "_vp.glsl" is appended for the vertex shader and /"_fp.glsl" is appended for the
     * fragment shader.*/
    void unloadShaderProgram(const std::string &relativePath);

    void loadTexture(const std::string &relativePath);
    model::Texture *getOrLoadTexture(const std::string &relativePath);
    void unloadTexture(const std::string &relativePath);

    void unloadAll();

private:
    std::string resourcesDirectory;

    std::unordered_map<std::string, model::Mesh *> meshes;
    std::unordered_map<std::string, GLuint> shaderPrograms;
    std::unordered_map<std::string, model::Texture *> textures;
};

}
}