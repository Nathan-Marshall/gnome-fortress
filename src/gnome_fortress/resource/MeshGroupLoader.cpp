#include "gnome_fortress/resource/MeshGroupLoader.h"

#include "gnome_fortress/resource/ResourceManager.h"
#include "objl/OBJ_Loader.h"

namespace gnome_fortress {
namespace resource {

model::MeshGroup *MeshGroupLoader::LoadMeshGroup(const std::string &filename, resource::ResourceManager &resourceManager){
    objl::Loader loader;
    if (!loader.LoadFile(filename)) {
        throw(std::ios_base::failure(std::string("Error loading OBJ model from file: ") + std::string(filename)));
    }

    model::MeshGroup *meshGroup = new model::MeshGroup();

    // Number of attributes for vertices and faces
    const int vertex_att = 11;
    const int face_att = 3;

    for (auto &mesh : loader.LoadedMeshes) {
        // Create OpenGL buffers and copy data
        GLuint vbo, ebo;

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.Vertices.size() * vertex_att * sizeof(GLfloat), 0, GL_STATIC_DRAW);
        // fill vertex buffer with data
        for (unsigned int vIndex = 0; vIndex < mesh.Vertices.size(); vIndex++) {
            GLfloat att[vertex_att] = { 0 };
            const objl::Vertex &vertex = mesh.Vertices[vIndex];

            // Position
            att[0] = vertex.Position.X;
            att[1] = vertex.Position.Y;
            att[2] = vertex.Position.Z;
            // Normal
            att[3] = vertex.Normal.X;
            att[4] = vertex.Normal.Y;
            att[5] = vertex.Normal.Z;
            // No color in (6, 7, 8)
            // Texture coordinates
            att[9] = vertex.TextureCoordinate.X;
            att[10] = vertex.TextureCoordinate.Y;

            // Copy attributes to buffer
            glBufferSubData(GL_ARRAY_BUFFER, vIndex * vertex_att * sizeof(GLfloat), vertex_att * sizeof(GLfloat), att);
        }

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.Indices.size() * sizeof(unsigned int), mesh.Indices.data(), GL_STATIC_DRAW);

        auto &mat = mesh.MeshMaterial;
        meshGroup->materials.push_back(
            new model::Material(
                mat.name,
                glm::vec3(mat.Ka.X, mat.Ka.Y, mat.Ka.Z),
                glm::vec3(mat.Kd.X, mat.Kd.Y, mat.Kd.Z),
                glm::vec3(mat.Ks.X, mat.Ks.Y, mat.Ks.Z),
                mat.Ns,
                mat.Ni,
                mat.d,
                mat.illum,
                std::string() == mat.map_Ka ? nullptr : resourceManager.getOrLoadTexture(GetRelativePathFromAbsolutePath(mat.map_Ka, resourceManager)),
                std::string() == mat.map_Kd ? nullptr : resourceManager.getOrLoadTexture(GetRelativePathFromAbsolutePath(mat.map_Kd, resourceManager)),
                std::string() == mat.map_Ks ? nullptr : resourceManager.getOrLoadTexture(GetRelativePathFromAbsolutePath(mat.map_Ks, resourceManager)),
                std::string() == mat.map_Ns ? nullptr : resourceManager.getOrLoadTexture(GetRelativePathFromAbsolutePath(mat.map_Ns, resourceManager)),
                std::string() == mat.map_d ? nullptr : resourceManager.getOrLoadTexture(GetRelativePathFromAbsolutePath(mat.map_d, resourceManager)),
                std::string() == mat.map_bump ? nullptr : resourceManager.getOrLoadTexture(GetRelativePathFromAbsolutePath(mat.map_bump, resourceManager))
            )
        );

        // create an instance of our own Mesh struct to store handles for the buffers
        meshGroup->meshes.push_back(new model::Mesh(mesh.MeshName, vbo, ebo, mesh.Vertices.size(), mesh.Indices.size(), GL_TRIANGLES, meshGroup->materials.back()));
    }

    return meshGroup;
}

//Delete the meshground from the loaded resources
void MeshGroupLoader::UnloadMeshGroup(model::MeshGroup *meshGroup) {
    for (auto mesh : meshGroup->meshes) {
        //Delete buffers associated with this mesh group
        glDeleteBuffers(1, &mesh->vbo);
        glDeleteBuffers(1, &mesh->ebo);
        delete mesh;
    }
    for (auto material : meshGroup->materials) {
        delete material;
    }
    delete meshGroup;
}

//Get a relative path from a given absolute path 
std::string MeshGroupLoader::GetRelativePathFromAbsolutePath(const std::string &filename, resource::ResourceManager &resourceManager) {
    std::string dir = resourceManager.getResourcesDirectory();
    if (filename.substr(0, dir.size()) == dir) {
        return filename.substr(dir.size());
    } else {
        throw(std::ios_base::failure(std::string("Given filename (\"") + filename
            + std::string("\") is not relative to the resources directory (\"") + dir + std::string("\").")));
    }
}

}
}