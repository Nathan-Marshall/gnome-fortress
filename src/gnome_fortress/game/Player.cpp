#include "gnome_fortress/game/Player.h"

#include "gnome_fortress/game/MushroomGun.h"
#include "gnome_fortress/game/PeanutGun.h"
#include "gnome_fortress/game/PineconeGun.h"
#include "gnome_fortress/game/Weapon.h"
#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {
    Player::Player(
            resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            RocketStreamTechnique *rocketStreamTechnique,
            Projectiles* projectiles,
            irrklang::ISoundEngine *soundEngine)
        : model::SceneNode(),
          //Create rocket streams for the jetpack
          rocketStream1(
              new RocketStream(resourceManager.getOrLoadTexture(resources::textures::flame4x4), rocketStreamTechnique)
          ),
          rocketStream2(
              new RocketStream(resourceManager.getOrLoadTexture(resources::textures::flame4x4), rocketStreamTechnique)
          ),
          //Initialize our movement variables
          forward(false),
          backward(false),
          left(false),
          right(false),
          up(false),
          down(false),
          velocity(),
          playerModel(new model::BasicMeshGroupNode(
              resourceManager.getOrLoadMeshGroup(resources::models::gnome),
              technique
          )),
          weaponContainer(new model::SceneNode()),
          currentWeapon(nullptr),
          weaponIndex(0)  {

        //Create the player model with its jetpack
        appendChild(playerModel);
        appendChild(rocketStream1);
        rocketStream1->setPosition(-0.1, 0.44, 0.1);
        rocketStream1->setRotation(glm::pi<float>(), glm::vec3(1, 0, 0));
        appendChild(rocketStream2);
        rocketStream2->setPosition(0.1, 0.44, 0.1);
        rocketStream2->setRotation(glm::pi<float>(), glm::vec3(1, 0, 0));

        //Append the weapon to the arm so that it appears in the players hand and not the player origin
        getArm()->appendChild(weaponContainer);
        weaponContainer->setPosition(0.14f, 0.48f, -0.15f);

        // Create weapons
        peanutGun = new PeanutGun(resourceManager, technique, this, projectiles, soundEngine);
        peanutGun->setVisible(false);
        weapons.push_back(peanutGun);
        weaponContainer->appendChild(peanutGun);

        mushroomGun = new MushroomGun(resourceManager, technique, this, projectiles, soundEngine);
        mushroomGun->setVisible(false);
        weapons.push_back(mushroomGun);
        weaponContainer->appendChild(mushroomGun);

        pineconeGun = new PineconeGun(resourceManager, technique, this, projectiles, soundEngine);
        pineconeGun->setVisible(false);
        weapons.push_back(pineconeGun);
        weaponContainer->appendChild(pineconeGun);

        setCurrentWeapon(peanutGun);
    }

    Player::~Player() {
        delete playerModel;
        delete weaponContainer;
        delete peanutGun;
        delete mushroomGun;
        delete pineconeGun;
    }

    //Set the scene boundaries for the player
    const float Player::XBOUND_POS = 35.0f;
    const float Player::XBOUND_NEG = -35.0f;
    const float Player::YBOUND_POS = 20.0f;
    const float Player::YBOUND_NEG = 0.0f;
    const float Player::ZBOUND_POS = 35.0f;
    const float Player::ZBOUND_NEG = -35.0f;

    //Set the player acceleration and decay factors
    const float Player::ACCELERATION = 8.0f;
    const float Player::DECAY = 0.5f;

    bool Player::IsForwardPressed() const {
        return forward;
    }
    bool Player::IsBackPressed() const {
        return backward;
    }
    bool Player::IsLeftPressed() const {
        return left;
    }
    bool Player::IsRightPressed() const {
        return right;
    }

    void Player::SetForwardPressed(bool isPressed) {
        forward = isPressed;
    }
    void Player::SetBackPressed(bool isPressed) {
        backward = isPressed;
    }
    void Player::SetLeftPressed(bool isPressed) {
        left = isPressed;
    }
    void Player::SetRightPressed(bool isPressed) {
        right = isPressed;
    }
    void Player::SetUpPressed(bool isPressed) {
        up = isPressed;
    }
    void Player::SetDownPressed(bool isPressed) {
        down = isPressed;
    }

    //Select the players weapon
    void Player::setCurrentWeapon(Weapon *newWeapon) {
        bool wasPressed = false;
        if (currentWeapon) {
            wasPressed = currentWeapon->isPressed();
            currentWeapon->setVisible(false);
            currentWeapon->setPressed(false);
        }
        
        newWeapon->setVisible(true);
        newWeapon->setPressed(wasPressed);
        newWeapon->setCooldown(glm::max(newWeapon->getCooldown(), 0.5f));
        currentWeapon = newWeapon;
    }

    Weapon *Player::getCurrentWeapon() const {
        return currentWeapon;
    }

    model::SceneNode *Player::getArm() const {
        return playerModel->getChild(2);
    }

    model::SceneNode *Player::getWeaponContainer() const {
        return weaponContainer;
    }

    void Player::nextWeapon() {
        weaponIndex++;
        if (weaponIndex >= weapons.size()) {
            weaponIndex = 0;
        }
        setCurrentWeapon(weapons[weaponIndex]);
    }

    void Player::prevWeapon() {
        weaponIndex--;
        if (weaponIndex < 0) {
            weaponIndex = weapons.size() - 1;
        }
        setCurrentWeapon(weapons[weaponIndex]);
    }

    //Update method for the player
    void Player::onUpdateSelf(float dt) {

        glm::vec3 acceleration;

        //Modify our velocity depending on our current movement direction
        if (forward) {
            acceleration = getRotation() * glm::vec3(0, 0, 1);
            velocity -= (acceleration * ACCELERATION) * dt;
        }
        if (backward) {
            acceleration = getRotation() * glm::vec3(0, 0, 1);
            velocity += (acceleration * ACCELERATION) * dt;
        }
        if (left) {
            acceleration = getRotation() * glm::vec3(1, 0, 0);
            velocity -= (acceleration * ACCELERATION) * dt;
        }
        if (right) {
            acceleration = getRotation() * glm::vec3(1, 0, 0);
            velocity += (acceleration * ACCELERATION) * dt;
        }
        if (up) {
            acceleration = getRotation() * glm::vec3(0, 1, 0);
            velocity += (acceleration * ACCELERATION) * dt;
        }
        if (down) {
            acceleration = getRotation() * glm::vec3(0, 1, 0);
            velocity -= (acceleration * ACCELERATION) * dt;
        }
        
        //Modify the jetpack power (how long and powerful the trail is) depending on whether we are moving up or down (or neither)
        if (up && !down) {
            rocketStream1->setPower(1.0f);
            rocketStream2->setPower(1.0f);
        } else if (down && !up) {
            rocketStream1->setPower(0.1f);
            rocketStream2->setPower(0.1f);
        } else {
            rocketStream1->setPower(0.4f);
            rocketStream2->setPower(0.4f);
        }

        //Add in our decay factor
        velocity *= glm::pow(DECAY, dt);

        //Check to make sure that we are within the scene bounds
        //This will modify the velocity to push us back if our velocity would move us out of bounds
        CheckBounds(velocity * dt);

        //If we are hitting a fence from the inside, translate towards the origin, and then set the velocity to 0 to stop the player from moving through fences
        if (hittingWallInside) {
            velocity = glm::normalize(getPosition() - glm::vec3(0, 0, 0));
            translate(velocity * -1.0f * dt);
            velocity = glm::vec3(0, 0, 0);
            hittingWallInside = false;
        }
        //Same as above, except we translate away from the origin
        else if (hittingWallOutside) {
            velocity = glm::normalize(getPosition() - glm::vec3(0, 0, 0));
            translate(velocity * 1.0f * dt);
            velocity = glm::vec3(0, 0, 0);
            hittingWallOutside = false;
        }
        //If we are hitting an enemy, move backwards and dampen our velocity
        else if (hittingEnemy) {
            translate(velocity * -1.0f * dt);
            velocity *= -0.5;
            hittingEnemy = false;
        }
        //If we have no movement conflicts as described above, we move freely with our given velocity
        else {
            translate(velocity * dt);
        }
        
    }

    //Check the player scene bounds and modify velocity accordingly
    void Player::CheckBounds(glm::vec3 translationAmount) {
        glm::vec3 currentPos = getPosition();
        glm::vec3 futurePos = currentPos += translationAmount;
        glm::vec3 localScale = getScale();

        float halfX = localScale.x / 2;
        float halfZ = localScale.z / 2;

        float diffX = 0;
        float diffY = 0;
        float diffZ = 0;

        //Adjust the player velocity based on where their velocity would currently take them
        if (futurePos.x + halfX > XBOUND_POS) {
            diffX = futurePos.x + halfX - XBOUND_POS;
        }
        if (futurePos.x - halfX < XBOUND_NEG) {
            diffX = futurePos.x - halfX - XBOUND_NEG;
        }
        if (futurePos.y + localScale.y > YBOUND_POS) {
            diffY = futurePos.y + localScale.y - YBOUND_POS;
        }
        if (futurePos.y < YBOUND_NEG) {
            diffY = futurePos.y - YBOUND_NEG;
        }
        if (futurePos.z + halfZ > ZBOUND_POS) {
            diffZ = futurePos.z + halfZ - ZBOUND_POS;
        }
        if (futurePos.z - halfZ < ZBOUND_NEG) {
            diffZ = futurePos.z - halfZ - ZBOUND_NEG;
        }

        velocity -= glm::vec3(diffX, diffY, diffZ);
    }

    //Process player collisions with walls and enemies
    void Player::ProcessCollisions(Walls* walls, Enemies* enemies) {
        //Process player collisions with the walls
        std::vector<std::vector<Wall*>>::iterator wallIt;
        std::vector<std::pair<glm::vec3, int>>::iterator holeIt;

        bool atHole = false;

        //Check each wall 'ring' to see if we would collide with it
        for (wallIt = walls->walls.begin(); wallIt < walls->walls.end(); wallIt++) {
            glm::vec3 playerPos = getPosition();

            if ((*wallIt).size() > 0) {
                glm::vec3 wallPos = (*wallIt)[0]->getPosition();

                float wallDist = glm::length(wallPos - glm::vec3(0, 0, 0));

                float dist = glm::length(playerPos - glm::vec3(0, 0, 0)) - wallDist;
                float ringDist = abs(dist);

                //If we would collide with this wall 'ring', we need to check if we are at a hole since that wouldn't count as a collision
                if (ringDist < Walls::WALL_WIDTH / 4 && playerPos.y < Walls::WALL_HEIGHT / 3) {
                    //Check to see if we are at a wall hole position
                    for (holeIt = walls->wallHoles.begin(); holeIt < walls->wallHoles.end(); holeIt++) {
                        float distToPlayer = glm::length(playerPos - (*holeIt).first);

                        if (distToPlayer < (*wallIt)[0]->GetLength() / 1.5) {
                            atHole = true;
                        }
                    }
                    if (!atHole) {
                        //We have a collision
                        if (dist > 0) {
                            hittingWallOutside = true;
                        }
                        else {
                            hittingWallInside = true;
                        }
                    }
                }
            }
        }


        //Process player collisions with enemies
        std::vector<SiegeTurtle*>::iterator turtleIt;
        std::vector<Squirrel*>::iterator squirrelIt;
        std::vector<Spider*>::iterator spiderIt;

        for (turtleIt = enemies->turtles.begin(); turtleIt < enemies->turtles.end(); turtleIt++) {
            glm::vec3 playerPos = getPosition();
            glm::vec3 turtlePos = (*turtleIt)->getPosition();

            //If the player is in the turtle bounding radius 
            if (glm::length(playerPos - turtlePos) < (*turtleIt)->GetBoundingRadius()) {
                //We have a collision
                hittingEnemy = true;
            }
        }
        for (squirrelIt = enemies->squirrels.begin(); squirrelIt < enemies->squirrels.end(); squirrelIt++) {
            glm::vec3 playerPos = getPosition();
            glm::vec3 squirrelPos = (*squirrelIt)->getPosition();

            //If the player is in the squirrel bounding radius 
            if (glm::length(playerPos - squirrelPos) < (*squirrelIt)->GetBoundingRadius()) {
                //We have a collision
                hittingEnemy = true;
            }
        }
        for (spiderIt = enemies->spiders.begin(); spiderIt < enemies->spiders.end(); spiderIt++) {
            glm::vec3 playerPos = getPosition();
            glm::vec3 spiderPos = (*spiderIt)->getPosition();

            //If the player is in the spider bounding radius 
            if (glm::length(playerPos - spiderPos) < (*spiderIt)->GetBoundingRadius()) {
                //We have a collision
                hittingEnemy = true;
            }
        }

        
        //Final check to see if the player would collide with the acorns
        if (glm::length(getPosition() - glm::vec3(0, 0, 0)) < 2.0 && getPosition().y < 2.0) {
            hittingWallOutside = true;
        }
    }
}
}