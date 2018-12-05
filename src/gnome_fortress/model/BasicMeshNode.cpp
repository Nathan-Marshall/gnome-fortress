#include "gnome_fortress/model/BasicMeshNode.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

namespace gnome_fortress {
namespace model {

BasicMeshNode::BasicMeshNode(
        const Mesh *mesh,
        renderer::BasicMeshNodeTechnique *technique)
    : mesh(mesh),
      backCulling(true),
      blendingEnabled(false),
      ambient_factor(0.3),
      env_map_factor(0),
      technique(technique) {

}

void BasicMeshNode::onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const {
    // if not blending, only draw during the first pass
    if (!blendingEnabled && pass != 0) {
        return;
    }

    // if blending, only draw during the second pass
    if (blendingEnabled && pass != 1) {
        return;
    }

    if (mesh) {
        // Set up z-buffer for rendering
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

        // Set culling of back faces
        if (backCulling) {
            glCullFace(GL_BACK);
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }

        if (blendingEnabled) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBlendEquation(GL_FUNC_ADD);
        } else {
            glDisable(GL_BLEND);
        }

        // bind buffers for mesh
        glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
        
        // set uniforms and bind textures
        technique->setAmbientFactor(ambient_factor);
        technique->setDiffuseColor(mesh->material->Kd);
        technique->setSpecularColor(mesh->material->Ks);
        technique->setSpecularExponent(mesh->material->Ns);
        technique->setAlpha(mesh->material->d);
        technique->bindDiffuseTexture(mesh->material->map_Kd);
        technique->bindGlossTexture(mesh->material->map_Ks);
        technique->bindAlphaTexture(mesh->material->map_d);

        // if env_map_factor is higher than 0, then bind the texture for environment mapping
        technique->setEnvMapFactor(env_map_factor);
        if (env_map_factor > 0) {
            technique->bindEnvMap();
        }

        // update model matrix
        technique->setModelMatrix(parent_transform * getTransformMatrix());

        // draw using technique
        technique->activate();
        glDrawElements(mesh->mode, mesh->num_elements, GL_UNSIGNED_INT, 0);
        technique->deactivate();
    }
}

const Mesh *BasicMeshNode::getMesh() const {
    return mesh;
}

renderer::BasicMeshNodeTechnique *BasicMeshNode::getTechnique() const {
    return technique;
}

void BasicMeshNode::setBackCulling(bool culling) {
    backCulling = culling;
}

void BasicMeshNode::setBlendingEnabled(bool enabled) {
    blendingEnabled = enabled;
}

void BasicMeshNode::setAmbientFactor(float factor) {
    ambient_factor = factor;
}

void BasicMeshNode::setEnvMapFactor(float factor) {
    env_map_factor = factor;
}

}
}