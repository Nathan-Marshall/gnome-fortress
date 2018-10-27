#include "gnome_fortress/game/Enemies.h"

namespace gnome_fortress {
namespace game {


Enemies::Enemies() {
	//Nothing yet
}

void Enemies::onDrawSelf(const glm::mat4 &parentTransform) const {
	for each (SiegeTurtle* turt in turtles)
	{
		turt->draw(glm::mat4());
	}
}

void Enemies::onUpdateSelf(float dt) {
	for each (SiegeTurtle* turt in turtles)
	{
		turt->update(dt);
	}
}

}
}