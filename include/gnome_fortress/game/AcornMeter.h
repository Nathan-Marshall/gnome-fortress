#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

#include "gnome_fortress/game/Acorns.h"
#include "gnome_fortress/ui/SpriteNode.h"

namespace gnome_fortress {
namespace game {

class AcornMeter : public ui::UINode {

public:
    AcornMeter(const Acorns *acorns, resource::ResourceManager &resourceManager, renderer::SpriteTechnique *technique);

    ~AcornMeter();

    virtual void onUpdateSelf(float delta_time) override;

private:
    const Acorns *acorns;
    std::vector<ui::SpriteNode*> acornIcons;
};

}
}