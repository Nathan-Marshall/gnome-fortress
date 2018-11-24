#include "gnome_fortress/game/Player.h"
#include "gnome_fortress/game/Weapon.h"
#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {
    Player::Player(
            resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique)
        : model::BasicMeshGroupNode(
            resourceManager.getOrLoadMeshGroup(resources::models::gnome),
            technique
          ),
          forward(false),
          backward(false),
          left(false),
          right(false),
          up(false),
          down(false),
          velocity(),
          currentWeapon(nullptr),
          weaponIndex(0)  {
        weaponContainer = new SceneNode();
        this->appendChild(weaponContainer);
    }

    Player::~Player() {
        delete weaponContainer;
    }

    const float Player::ACCELERATION = 7.0f;
    const float Player::DECAY = 0.20f;

    bool Player::IsForwardPressed() {
        return forward;
    }
    bool Player::IsBackPressed() {
        return backward;
    }
    bool Player::IsLeftPressed() {
        return left;
    }
    bool Player::IsRightPressed() {
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

    model::SceneNode* Player::getWeaponContainer() {
        return weaponContainer;
    }

    Weapon* Player::getCurrentWeapon() {
        return currentWeapon;
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
        else if (backward) {
            acceleration = getRotation() * glm::vec3(0, 0, 1);
            velocity += (acceleration * ACCELERATION) * dt;
        }
        else if (left) {
            acceleration = getRotation() * glm::vec3(1, 0, 0);
            velocity -= (acceleration * ACCELERATION) * dt;
        }
        else if (right) {
            acceleration = getRotation() * glm::vec3(1, 0, 0);
            velocity += (acceleration * ACCELERATION) * dt;
        }

        else if (up) {
            acceleration = getRotation() * glm::vec3(0, 1, 0);
            velocity += (acceleration * ACCELERATION) * dt;
        }
        else if (down) {
            acceleration = getRotation() * glm::vec3(0, 1, 0);
            velocity -= (acceleration * ACCELERATION) * dt;
        }

        velocity *= glm::pow(DECAY, dt);

        CheckBounds(velocity * dt);

        translate(velocity * dt);
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
}
}