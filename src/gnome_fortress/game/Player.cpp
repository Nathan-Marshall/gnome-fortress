#include "gnome_fortress/game/Player.h"
#include "gnome_fortress/game/Weapon.h"
#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {
    Player::Player(
            resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            RocketStreamTechnique *rocketStreamTechnique)
        : model::SceneNode(),
          rocketStream1(
              new RocketStream(resourceManager.getOrLoadTexture(resources::textures::flame4x4), rocketStreamTechnique)
          ),
          rocketStream2(
              new RocketStream(resourceManager.getOrLoadTexture(resources::textures::flame4x4), rocketStreamTechnique)
          ),
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

        appendChild(playerModel);
        appendChild(rocketStream1);
        rocketStream1->setPosition(-0.1, 0.44, 0.1);
        rocketStream1->setRotation(glm::pi<float>(), glm::vec3(1, 0, 0));
        appendChild(rocketStream2);
        rocketStream2->setPosition(0.1, 0.44, 0.1);
        rocketStream2->setRotation(glm::pi<float>(), glm::vec3(1, 0, 0));

        getArm()->appendChild(weaponContainer);
        weaponContainer->setPosition(0.14f, 0.48f, -0.15f);
    }

    Player::~Player() {
        delete playerModel;
        delete weaponContainer;
    }

    const float Player::XBOUND_POS = 35.0f;
    const float Player::XBOUND_NEG = -35.0f;
    const float Player::YBOUND_POS = 20.0f;
    const float Player::YBOUND_NEG = 0.0f;
    const float Player::ZBOUND_POS = 35.0f;
    const float Player::ZBOUND_NEG = -35.0f;

    const float Player::ACCELERATION = 7.0f;
    const float Player::DECAY = 0.20f;

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

    void Player::setCurrentWeapon(Weapon *newWeapon) {
        if (!currentWeapon) {
            weaponContainer->appendChild(newWeapon);
        }
        else {
            weaponContainer->replaceChild(newWeapon, weaponContainer->indexOf(currentWeapon));
        }
        
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

    void Player::incrementWeaponIndex() {
            weaponIndex++;
    }

    void Player::decrementWeaponIndex() {
            weaponIndex--;
    }

    void Player::setWeaponIndex(int index) {
        weaponIndex = index;
    }

    const int Player::getWeaponIndex() {
        return weaponIndex;
    }

    void Player::onUpdateSelf(float dt) {

        glm::vec3 acceleration;

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

        velocity *= glm::pow(DECAY, dt);

        CheckBounds(velocity * dt);

        if (hittingWallInside) {
            velocity = glm::normalize(getPosition() - glm::vec3(0, 0, 0));
            translate(velocity * -1.0f * dt);
            velocity = glm::vec3(0, 0, 0);
            hittingWallInside = false;
        }
        else if (hittingWallOutside) {
            velocity = glm::normalize(getPosition() - glm::vec3(0, 0, 0));
            translate(velocity * 1.0f * dt);
            velocity = glm::vec3(0, 0, 0);
            hittingWallOutside = false;
        }
        else {
            translate(velocity * dt);
        }
        
    }

    void Player::CheckBounds(glm::vec3 translationAmount) {
        glm::vec3 currentPos = getPosition();
        glm::vec3 futurePos = currentPos += translationAmount;
        glm::vec3 localScale = getScale();

        float halfX = localScale.x / 2;
        float halfZ = localScale.z / 2;

        float diffX = 0;
        float diffY = 0;
        float diffZ = 0;

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

    void Player::ProcessCollisions(Walls* walls) {
        //Process player collisions with the walls
        std::vector<std::vector<Wall*>>::iterator wallIt;
        std::vector<std::pair<glm::vec3, int>>::iterator holeIt;

        bool atHole = false;

        for (wallIt = walls->walls.begin(); wallIt < walls->walls.end(); wallIt++) {
            glm::vec3 playerPos = getPosition();

            if ((*wallIt)[0]) {
                glm::vec3 wallPos = (*wallIt)[0]->getPosition();

                float wallDist = glm::length(wallPos - glm::vec3(0, 0, 0));

                float dist = glm::length(playerPos - glm::vec3(0, 0, 0)) - wallDist;
                float ringDist = abs(dist);
                
                if (ringDist < Walls::WALL_WIDTH / 4 && playerPos.y < Walls::WALL_HEIGHT / 3) {
                    //Check to see if we are at a wall hole position
                    for (holeIt = walls->wallHoles.begin(); holeIt < walls->wallHoles.end(); holeIt++) {
                        float distToPlayer = glm::length(playerPos - (*holeIt).first);

                        if (distToPlayer < (*wallIt)[0]->GetLength() / 2) {
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
    }
}
}