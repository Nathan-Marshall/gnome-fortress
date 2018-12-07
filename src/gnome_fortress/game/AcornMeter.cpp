#include "gnome_fortress/game/AcornMeter.h"

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {

AcornMeter::AcornMeter(const Acorns *acorns, resource::ResourceManager &resourceManager, renderer::SpriteTechnique *technique)
    : acorns(acorns),
      acornIcons(Acorns::NUM_ACORNS) {

    for (int i = 0; i < Acorns::NUM_ACORNS; i++) {
        ui::SpriteNode *icon = new ui::SpriteNode(resourceManager.getOrLoadTexture(resources::textures::ui_acorn), technique);
        acornIcons[i] = icon;
        icon->setScale(0.04f, 0.05f);
        icon->setPosition(-1 + icon->getScale().x + 0.01f + (icon->getScale().x + 0.01f) * i, 1 - icon->getScale().y - 0.01f);
        appendChild(icon);
    }
}

AcornMeter::~AcornMeter(){
    for each (auto icon in acornIcons) {
        delete icon;
    }
}

void AcornMeter::onUpdateSelf(float delta_time) {
    for (int i = 0; i < Acorns::NUM_ACORNS; i++) {
        if (i >= acorns->getRemainingAcornCount()) {
            acornIcons[i]->setScale(0);
        } else if(i == static_cast<int>(acorns->getRemainingAcornCount()) - 1) {
            acornIcons[i]->setScale(0.04f, 0.05f);
            acornIcons[i]->scale(acorns->getRemainingAcornCount() - 1 - i);
        }
    }
}

} //namespace game
} //namespace gnome_fortress 