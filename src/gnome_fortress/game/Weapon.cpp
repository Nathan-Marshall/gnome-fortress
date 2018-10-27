#include "gnome_fortress/game/Weapon.h"
#include <iostream>

namespace gnome_fortress {
namespace game {
 Weapon::Weapon(const model::Mesh *gunMesh, const model::Mesh *bMesh,
    renderer::BasicProjectionTechnique *technique, Player *player)
    : model::BasicMeshNode(gunMesh, technique),
     firing(false)
 {
    bulletMesh = bMesh;
    setPosition(0.8, 0, 0);
    setScale(0.2, 0.4, 0.8);

	/* Potential scaling for gnome-sized guns
		setScale(0.1, 0.2, 0.5);*/
}

    //These should be set based on the kind of gun created 
    int FIRING_RATE = 5;
	double FIRING_VELOCITY = 5.0;

Weapon::~Weapon() { 
}

bool Weapon::isFiring() {
	return firing;
}

void Weapon::setFiring(bool isPressed) {
	firing = isPressed;
}

float Weapon::getCooldown() {
	return cooldown;
}

void Weapon::setCooldown(float cd) {
	cooldown = cd;
}

Projectile* Weapon::fireBullet(glm::vec3 position, glm::quat cameraRotation) {
	glm::vec3 vel = glm::normalize(glm::vec3(getGlobalTransform() * glm::mat4_cast(cameraRotation) * glm::vec4(0, 0, -1, 0)));
	vel.x *= 5.0; //FIRING_VELOCITY;
	vel.y *= 5.0; //FIRING_VELOCITY;
	vel.z *= 5.0; //FIRING_VELOCITY;
	Projectile *p = new Projectile(bulletMesh, getTechnique(),
		glm::vec3(getGlobalTransform() * glm::vec4(0,0,0,1)), vel);
	return p;
}

void Weapon::onUpdateSelf(float delta_time) {
    cooldown -= delta_time;

	// DEBUG stuff
	/*std::cout << "WEAPON POSITION-- x: " << getPosition().x
		<< ", y: " << getPosition().y
		<< ", z: " << getPosition().z
		<< std::endl;*/

/*	std::cout << "VELOCITY-- x: " << velocity.x
		<< ", y: " << velocity.y
		<< ", z: " << velocity.z
		<< std::endl;*/
}


}
}