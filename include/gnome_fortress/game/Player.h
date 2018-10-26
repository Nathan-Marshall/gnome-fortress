#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "gnome_fortress/model/BasicMeshNode.h"

namespace gnome_fortress{
namespace game{

class Player : public model::BasicMeshNode {

public:
	Player(const model::Mesh *mesh,
            const model::Texture *texture,
		    renderer::BasicMeshNodeTechnique *technique);

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

protected:
	void onUpdateSelf(float dt) override;

private:
	bool forward;
	bool backward;
	bool left;
	bool right;

	glm::vec3 velocity;
};
}
}