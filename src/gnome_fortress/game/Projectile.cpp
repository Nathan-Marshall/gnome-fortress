#include "gnome_fortress/game/Projectile.h"
#include <iostream>

namespace gnome_fortress {
namespace game {
    Projectile::Projectile(
            const model::Mesh *mesh,
            const model::Texture *diffuse_texture,
            renderer::BasicMeshNodeTechnique *technique, 
		    glm::vec3 pointOfOrigin,
            glm::vec3 velocity)
        : model::BasicMeshNode(mesh, diffuse_texture, technique),
        velocity(velocity), 
		lifespan(0)
	{
		pointOfOrigin.z = pointOfOrigin.z;
		setPosition(pointOfOrigin);

		//Make the bullets nice and smol
		setScale(0.09, 0.09, 0.09);

		//Get the axis we should rotate around
        glm::vec3 axis = glm::cross(glm::vec3(0, 0, -1), velocity); //axis to rotate around 

		//Get the angle we should rotate around this axis
		float angle = acos((glm::dot(velocity, glm::vec3(0, 0, -1))) / glm::length(velocity));
		
		//Rotate around the axis
		rotate(angle, glm::normalize(axis));

		//Rotate by 90 degrees so the cylinder is 'facing forward'
		rotate(90 * (glm::pi<float>() / 180.0f), glm::vec3(1.0, 0.0, 0.0));

    }

	const int DAMAGE = 10; //SHOULD BE BASED ON WEAPON, WHO CARES RN THO

	Projectile::~Projectile() {
		delete this->mesh;
	}

	glm::vec3 Projectile::getVelocity(){
		return velocity;
	}

	void Projectile::onUpdateSelf(float dt) {
		
        setPosition(getPosition() + (velocity * dt));

		
		/*std::cout << "POSITION-- x: " << getPosition().x
			<< ", y: " << getPosition().y
			<< ", z: " << getPosition().z
			<< std::endl;

		std::cout << "VELOCITY-- x: " << velocity.x
			<< ", y: " << velocity.y
			<< ", z: " << velocity.z
			<< std::endl;*/
		

		//if collision, or has travelled super far, delete
		/*lifespan += dt;
		if (lifespan > 30) {
			//delete self
		}*/

	}
}
}