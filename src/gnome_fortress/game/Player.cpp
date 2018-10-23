#include "gnome_fortress/game/Player.h"

namespace gnome_fortress {
namespace game {
	Player::Player(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique)
		: model::BasicMeshNode(mesh, technique),
		  forward(false),
		  backward(false),
		  left(false),
		  right(false),
		  up(false),
		  down(false),
		  velocity() {
		//Nothing yet
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

	void Player::onUpdateSelf(float dt) {

		if (forward) {
			velocity.z -= ACCELERATION * dt;
		}
		else if (backward) {
			velocity.z += ACCELERATION * dt;
		}
		else if (left) {
			velocity.x -= ACCELERATION * dt;
		}
		else if (right) {
			velocity.x += ACCELERATION * dt;
		}
		else if (up) {
			velocity.y += ACCELERATION * dt;
		}
		else if (down) {
			velocity.y -= ACCELERATION * dt;
		}
		velocity *= glm::pow(DECAY, dt);

		translate(getRotation() * velocity * dt);
	}
}
}