#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshGroupNode.h"
#include "gnome_fortress/resource/ResourceManager.h"


namespace gnome_fortress{
namespace game{

class Weapon;

class Player : public model::BasicMeshGroupNode {

public:
    Player(resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique);

    ~Player();

    const static float ACCELERATION;
    const static float DECAY;
    
    bool IsForwardPressed();
    bool IsBackPressed();
    bool IsLeftPressed();
    bool IsRightPressed();

    void SetForwardPressed(bool isPressed);
    void SetBackPressed(bool isPressed);
    void SetLeftPressed(bool isPressed);
    void SetRightPressed(bool isPressed);
    void SetUpPressed(bool isPressed);
    void SetDownPressed(bool isPressed);

    void setCurrentWeapon(Weapon *weapon);
    Weapon* getCurrentWeapon();

    SceneNode* getWeaponContainer();

    void incrementWeaponIndex();
    void decrementWeaponIndex();
    void setWeaponIndex(int index);
    const int getWeaponIndex();

protected:
    void onUpdateSelf(float dt) override;

private:
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool up;
    bool down;

    SceneNode *weaponContainer;
    Weapon *currentWeapon;

    int weaponIndex;

    glm::vec3 velocity;

    void CheckBounds(glm::vec3 translationAmount);
};
}
}