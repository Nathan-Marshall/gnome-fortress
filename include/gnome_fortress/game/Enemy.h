#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshGroupNode.h"
#include "irrKlang\irrKlang.h"

namespace gnome_fortress {
namespace game {


class Enemy : public model::BasicMeshGroupNode {

public:
    Enemy(const model::MeshGroup *meshGroup,
        renderer::BasicMeshNodeTechnique *technique);

    float GetBoundingRadius();
    float GetHealth();
    const char* GetAttackSound();

    void DoDamage(float damage);

    void PlayAttackSound();
protected:
    void onUpdateSelf(float dt) override;

    float health;
    float boundingRadius;
    float moveSpeed;

    const char* attackSoundByte;
    irrklang::ISoundEngine *soundEngine;

    float timer;

private:
    
};


}
}