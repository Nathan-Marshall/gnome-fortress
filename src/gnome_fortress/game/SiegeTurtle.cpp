#include "gnome_fortress/game/SiegeTurtle.h"

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {


SiegeTurtle::SiegeTurtle(
        resource::ResourceManager &resourceManager,
        renderer::BasicMeshNodeTechnique *technique)
	: game::Enemy(
        resourceManager.getOrLoadMesh(resources::models::siege_turtle),
        resourceManager.getOrLoadTexture("models/siege_turtle/siege_turtle.png"),
        technique
      ) {
	setScale(1.0f);
	//Get an angle for the random placement of the siege turtle 
	//Random is temporary
	float angle = (rand() % 360) * (glm::pi<float>() / 180.0f);
	setPosition(glm::vec3(30 * cos(angle), 1, 30 * sin(angle)));
}


void SiegeTurtle::onUpdateSelf(float dt) {
	//For now, the siege turtle will just move to the origin
	glm::vec3 moveDir = glm::normalize(getPosition() - glm::vec3(0, 0, 0));
	translate(glm::vec3(-moveDir.x, -moveDir.y, -moveDir.z) * dt);
}


}
}