#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/RocketStream.h"
#include "gnome_fortress/model/BasicMeshGroupNode.h"
#include "gnome_fortress/resource/ResourceManager.h"


namespace gnome_fortress{
namespace game{

class Weapon;

class Player : public model::SceneNode {

public:
    Player(resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            RocketStreamTechnique *rocketStreamTechnique);

    ~Player();

    //GLOBAL SCENE BOUNDS
    const static float XBOUND_POS;
    const static float XBOUND_NEG;

    const static float YBOUND_POS;
    const static float YBOUND_NEG;

    const static float ZBOUND_POS;
    const static float ZBOUND_NEG;


    const static float ACCELERATION;
    const static float DECAY;
    
    bool IsForwardPressed() const;
    bool IsBackPressed() const;
    bool IsLeftPressed() const;
    bool IsRightPressed() const;

    void SetForwardPressed(bool isPressed);
    void SetBackPressed(bool isPressed);
    void SetLeftPressed(bool isPressed);
    void SetRightPressed(bool isPressed);
    void SetUpPressed(bool isPressed);
    void SetDownPressed(bool isPressed);

    void setCurrentWeapon(Weapon *weapon);
    Weapon *getCurrentWeapon() const;

    model::SceneNode *getArm() const;
    model::SceneNode *getWeaponContainer() const;

    void incrementWeaponIndex();
    void decrementWeaponIndex();
    void setWeaponIndex(int index);
    const int getWeaponIndex();

protected:
    void onUpdateSelf(float dt) override;

private:
    RocketStream *rocketStream1;
    RocketStream *rocketStream2;

    bool forward;
    bool backward;
    bool left;
    bool right;
    bool up;
    bool down;

    glm::vec3 velocity;

    model::BasicMeshGroupNode *playerModel;
    SceneNode *weaponContainer;
    Weapon *currentWeapon;

    int weaponIndex;

    void CheckBounds(glm::vec3 translationAmount);
};
}
}