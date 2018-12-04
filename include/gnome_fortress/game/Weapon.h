#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/Player.h"
#include "gnome_fortress/game/Projectiles.h"
#include "irrKlang\irrKlang.h"

namespace gnome_fortress {
namespace game {

class Weapon : public model::BasicMeshGroupNode {
    
public: 
    Weapon(const model::MeshGroup *gunMeshGroup,
        const model::MeshGroup *bMeshGroup,
        renderer::BasicMeshNodeTechnique *technique, 
        Player *player);

    ~Weapon();

    //Whether the weapon is firing
    bool isPressed();
    void setPressed(bool isPressed);

    //Gun cooldown 
    float getCooldown();
    void setCooldown(float cd);

    //Creating bullets 
    virtual std::vector<Projectile*> fireBullet(glm::vec3 position);

    void PlayWeaponSound();

protected:
    const model::MeshGroup *bulletMeshGroup;
    
    bool pressed;
    float cooldown;

    const char* fireSoundByte;
    irrklang::ISoundEngine *soundEngine;

};
}
}