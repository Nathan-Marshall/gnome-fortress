#pragma once

#include <string>
#include <unordered_map>

#include <gnome_fortress/model/MeshGroup.h>

namespace gnome_fortress {
namespace resource {

class ResourceManager {
public:
    ResourceManager(const std::string &resourcesDirectory);
    ~ResourceManager();

    std::string getResourcesDirectory() const;

    void loadMeshGroup(const std::string &relativePath);
    model::MeshGroup *getOrLoadMeshGroup(const std::string &relativePath);
    void unloadMeshGroup(const std::string &relativePath);

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

    //Load the full path of the audio clip
    void loadAudioClip(const std::string &relativePath);
    const char* getOrLoadAudioClip(const std::string &relativePath);

    void loadTexture(const std::string &relativePath);
    model::Texture *getOrLoadTexture(const std::string &relativePath);
    /* When dealing with skyboxes, ResourceManager expects a filename prefix, which refers to 6 separate images.
     * Each of "_xn.[ext]", "_xp.[ext]", "_yn.[ext]", "_yp.[ext]", "_zn.[ext]", "_zp.[ext]" is appended, one for each
     * side of the cube map. */
    void loadSkyboxTexture(const std::string &relativePath);
    /* When dealing with skyboxes, ResourceManager expects a filename prefix, which refers to 6 separate images.
     * Each of "_xn.[ext]", "_xp.[ext]", "_yn.[ext]", "_yp.[ext]", "_zn.[ext]", "_zp.[ext]" is appended, one for each
     * side of the cube map. */
    model::Texture *getOrLoadSkyboxTexture(const std::string &relativePath);
    void unloadTexture(const std::string &relativePath);

    void unloadAll();

private:
    std::string resourcesDirectory;

    std::unordered_map<std::string, model::MeshGroup *> meshGroups;
    std::unordered_map<std::string, GLuint> shaderPrograms;
    std::unordered_map<std::string, model::Texture *> textures;
    std::unordered_map<std::string, std::string> audioClips;
};

}
}