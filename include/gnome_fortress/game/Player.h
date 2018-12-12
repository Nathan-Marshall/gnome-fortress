#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/game/RocketStream.h"
#include "gnome_fortress/model/BasicMeshGroupNode.h"
#include "gnome_fortress/resource/ResourceManager.h"

#include "Walls.h"
#include "Enemies.h"


namespace gnome_fortress{
namespace game{

class Weapon;

class Player : public model::SceneNode {

public:
    Player(resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            RocketStreamTechnique *rocketStreamTechnique,
            Projectiles* projectiles,
            irrklang::ISoundEngine *soundEngine);

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
    
    //Booleans to track which buttons are being pressed
    bool IsForwardPressed() const;
    bool IsBackPressed() const;
    bool IsLeftPressed() const;
    bool IsRightPressed() const;

    //Set which buttons are being pressed
    void SetForwardPressed(bool isPressed);
    void SetBackPressed(bool isPressed);
    void SetLeftPressed(bool isPressed);
    void SetRightPressed(bool isPressed);
    void SetUpPressed(bool isPressed);
    void SetDownPressed(bool isPressed);

    //Selecting and getting the player weapon
    Weapon *getCurrentWeapon() const;

    model::SceneNode *getArm() const;
    model::SceneNode *getWeaponContainer() const;

    //Methods for changing weapons
    void nextWeapon();
    void prevWeapon();

    //Process player collisions
    void ProcessCollisions(Walls* walls, Enemies* enemies);

protected:
    void onUpdateSelf(float dt) override;

private:
    void setCurrentWeapon(Weapon *weapon);

    //Rocket streams to be used for our jetpack
    RocketStream *rocketStream1;
    RocketStream *rocketStream2;

    //Movement booleans
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool up;
    bool down;

    //Collision booleans
    bool hittingWallInside;
    bool hittingWallOutside;
    bool hittingEnemy;

    glm::vec3 velocity;

    //Player and weapon nodes
    model::BasicMeshGroupNode *playerModel;
    SceneNode *weaponContainer;

    std::vector<Weapon*> weapons;
    game::Weapon *peanutGun;
    game::Weapon *mushroomGun;
    game::Weapon *pineconeGun;

    Weapon *currentWeapon;
    int weaponIndex;

    //Check that the player respects the scene boundaries
    void CheckBounds(glm::vec3 translationAmount);
};
}
}