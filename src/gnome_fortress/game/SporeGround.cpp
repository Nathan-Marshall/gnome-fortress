#include "gnome_fortress/game/SporeGround.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace game {

    SporeGround::SporeGround(const model::Texture *texture, SporeGroundTechnique *technique)
    : pointSet(CreateSphericalParticles(3000)),
      texture(texture),
      technique(technique),
      power(1.0f) {
}

    SporeGround::~SporeGround() {
    glDeleteBuffers(1, &pointSet->vbo);
    delete pointSet;
}

void SporeGround::setPower(float p) {
    power = p;
}

void SporeGround::onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const {
    // ONLY DRAW DURING THE BLEND PASS
    if (pass != 1) {
        return;
    }

    // Set up z-buffer for rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // don't write to the depth buffer or we won't see the nice blending on the particles
    glDepthMask(GL_FALSE);

    // Set culling of back faces
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // enable blending
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_MAX);

    // bind buffers for mesh
    glBindBuffer(GL_ARRAY_BUFFER, pointSet->vbo);

    // bind texture (cube map)
    technique->bindMainTexture(texture);

    // update model matrix
    technique->setModelMatrix(parent_transform * getTransformMatrix());

    // update power to use the value of this RocketStream instance
    technique->setPower(power);

    // draw using technique
    technique->activate();
    glDrawArrays(pointSet->mode, 0, pointSet->num_vertices);
    technique->deactivate();

    // reset writing to the depth buffer or bad things happen
    glDepthMask(GL_TRUE);
}

const model::PointSet *SporeGround::getPointSet() const {
    return pointSet;
}

SporeGroundTechnique *SporeGround::getTechnique() const {
    return technique;
}

model::PointSet *SporeGround::CreateSphericalParticles(int num_particles) {
    // Create a set of points which will be the particles

    // Data buffer
    GLfloat *particle = nullptr;

    // Number of attributes per particle: position (3), normal (3), and color (3)
    const int particle_att = 9;

    // Allocate memory for buffer
    try {
        particle = new GLfloat[num_particles * particle_att];
    } catch (std::exception &e) {
        throw e;
    }

    float spreadAngle = 90.0f * glm::pi<float>() / 180.0f;
    float circleRad = tan(spreadAngle);
    float distAngle;
    float circDist;

    for (int i = 0; i < num_particles; i++) {
        distAngle = rand() / (float)RAND_MAX * (glm::pi<float>() * 2);
        circDist = rand() / (float)RAND_MAX * circleRad;
        circDist *= circDist / circleRad;

        glm::vec3 dir = glm::normalize(glm::vec3(circDist * cos(distAngle), 1, circDist * sin(distAngle)));

        // Define the normal and point based on theta, phi and the spray
        glm::vec3 normal = dir / 4.0f;
        glm::vec3 position(0);
        glm::vec3 color(i / (float)num_particles, 0.0, 1.0 - (i / (float)num_particles)); // We can use the color for debug, if needed

        // Add vectors to the data buffer
        for (int k = 0; k < 3; k++) {
            particle[i*particle_att + k] = position[k];
            particle[i*particle_att + k + 3] = normal[k];
            particle[i*particle_att + k + 6] = color[k];
        }
    }

    // Create OpenGL buffer and copy data
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, num_particles * particle_att * sizeof(GLfloat), particle, GL_STATIC_DRAW);

    // Free data buffers
    delete[] particle;

    // Create resource
    return new model::PointSet("Spore Ground", vbo, num_particles, GL_POINTS);
}

}
}