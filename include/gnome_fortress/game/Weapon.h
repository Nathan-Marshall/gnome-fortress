#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshNode.h"
#include "gnome_fortress/game/Player.h"
#include "gnome_fortress/game/Projectile.h"

namespace gnome_fortress {
namespace game {

class Weapon : public model::BasicMeshNode {
	
public: 
    Weapon(const model::Mesh *gunMesh,
        const model::Mesh *bMesh,
        const model::Texture *gun_diffuse_texture,
        const model::Texture *bullet_diffuse_texture,
        renderer::BasicMeshNodeTechnique *technique, 
        Player *player);

    ~Weapon();

    //Whether the weapon is firing
    bool isFiring();
	void setFiring(bool isPressed);

	//Gun cooldown 
	float getCooldown();
	void setCooldown(float cd);

	//Creating bullets 
	Projectile* fireBullet(glm::vec3 position, glm::quat cameraRotation);
	

	void onUpdateSelf(float dt) override;

private:
	static int FIRING_RATE; //number of bullets per second 
	static double FIRING_VELOCITY; //speed of individual bullets 

	const model::Mesh *bulletMesh;
    const model::Texture *bullet_diffuse_texture;
	
	bool firing;
	float cooldown;

};
}
}