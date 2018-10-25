#include "gnome_fortress/game/Projectile.h"
#include <iostream>

namespace gnome_fortress {
namespace game {
    Projectile::Projectile(const model::Mesh *mesh, renderer::BasicProjectionTechnique *technique, 
		glm::vec3 pointOfOrigin, glm::vec3 velocity)
        : model::BasicMeshNode(mesh, technique),
        velocity(velocity), 
		lifespan(0)
	{
		pointOfOrigin.z = pointOfOrigin.z  * 1.25; 
		setPosition(pointOfOrigin);
		//Removed while debugging for clarity
		//setScale(0.09, 0.09, 0.09);
		
        glm::vec3 axis = glm::cross(glm::vec3(0, 0, -1), glm::normalize(velocity)); //axis to rotate around 
		float angle = glm::asin(glm::length(axis));
		glm::vec3 test = glm::normalize(axis);
		rotate(angle + glm::pi<float>(), axis); //garbage that needs fixing

		rotate(90 * glm::pi<float>() / 180.0f, glm::vec3(1.0, 0.0, 0.0));

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