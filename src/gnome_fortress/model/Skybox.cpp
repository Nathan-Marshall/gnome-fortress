#include "gnome_fortress/model/Skybox.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace model {

Skybox::Skybox(const Texture *texture, renderer::SkyboxTechnique *technique)
    : mesh(nullptr),
      texture(texture),
      technique(technique) {

    mesh = GenerateMesh();
}

Skybox::~Skybox() {
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteBuffers(1, &mesh->ebo);
    delete mesh;
}

void Skybox::onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const {
    // only draw during the first pass (no blending)
    if (pass != 0) {
        return;
    }

    // Set up z-buffer for rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Set culling of back faces
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // disable blending
    glDisable(GL_BLEND);

    // bind buffers for mesh
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);

    // bind texture (cube map)
    technique->bindSkyboxTexture(texture);

    // update model matrix
    technique->setModelMatrix(parent_transform * getTransformMatrix());

    // draw using technique
    technique->activate();
    glDrawElements(mesh->mode, mesh->num_elements, GL_UNSIGNED_INT, 0);
    technique->deactivate();
}

const Mesh *Skybox::getMesh() const {
    return mesh;
}

renderer::SkyboxTechnique *Skybox::getTechnique() const {
    return technique;
}

model::Mesh *Skybox::GenerateMesh() {
    // Each face of the cube is defined by four vertices (with the same normal) and two triangles
    GLfloat d = 1;

    // Vertices that form the cube
    // 9 attributes per vertex: 3D position (3), 3D normal (3)
    GLfloat vertices[] = {
        // First cube face
        -d, -d,  d,    0,  0, -1,
         d, -d,  d,    0,  0, -1,
         d,  d,  d,    0,  0, -1,
        -d,  d,  d,    0,  0, -1,
        // Second cube face
         d, -d,  d,   -1,  0,  0,
         d, -d, -d,   -1,  0,  0,
         d,  d, -d,   -1,  0,  0,
         d,  d,  d,   -1,  0,  0,
        // Third cube face
         d, -d, -d,    0,  0,  1,
        -d, -d, -d,    0,  0,  1,
        -d,  d, -d,    0,  0,  1,
         d,  d, -d,    0,  0,  1,
        // Fourth cube face
        -d, -d, -d,    1,  0,  0,
        -d, -d,  d,    1,  0,  0,
        -d,  d,  d,    1,  0,  0,
        -d,  d, -d,    1,  0,  0,
        // Fifth cube face
        -d,  d,  d,    0, -1,  0,
         d,  d,  d,    0, -1,  0,
         d,  d, -d,    0, -1,  0,
        -d,  d, -d,    0, -1,  0,
        // Sixth cube face
         d, -d,  d,    0,  1,  0,
        -d, -d,  d,    0,  1,  0,
        -d, -d, -d,    0,  1,  0,
         d, -d, -d,    0,  1,  0,
    };

    GLuint elements[] = {
        // First cube face
        0, 2, 1,
        0, 3, 2,
        // Second cube face
        4, 6, 5,
        4, 7, 6,
        // Third cube face
        8, 10, 9,
        8, 11, 10,
        // Fourth cube face
        12, 14, 13,
        12, 15, 14,
        // Fifth cube face
        16, 18, 17,
        16, 19, 18,
        // Sixth cube face
        20, 22, 21,
        20, 23, 22
    };

    GLuint num_vertices = sizeof(vertices) / sizeof(GLfloat) / 6;
    GLuint num_elements = sizeof(elements) / sizeof(GLuint);

    // Create OpenGL buffers and copy data
    GLuint vbo, ebo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Create mesh 
    return new Mesh("Skybox", vbo, ebo, num_vertices, num_elements, GL_TRIANGLES, nullptr);
}

}
}