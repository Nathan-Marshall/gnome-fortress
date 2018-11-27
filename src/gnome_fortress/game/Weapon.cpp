#include "gnome_fortress/game/Weapon.h"
#include <iostream>

//These should be set based on the kind of gun created 
int FIRING_RATE = 5;
double FIRING_VELOCITY = 5.0;

namespace gnome_fortress {
namespace game {

Weapon::Weapon(
        const model::MeshGroup *gunMeshGroup,
        const model::MeshGroup *bMeshGroup,
        renderer::BasicMeshNodeTechnique *technique,
        Player *player)
    : model::BasicMeshGroupNode(gunMeshGroup, technique),
      pressed(false), 
      bulletMeshGroup(bMeshGroup) {
}

Weapon::~Weapon() { 
}

bool Weapon::isPressed() {
    return pressed;
}

void Weapon::setPressed(bool isPressed) {
    pressed = isPressed;
}

float Weapon::getCooldown() {
    return cooldown;
}

void Weapon::setCooldown(float cd) {
    cooldown = cd;
}


}
}