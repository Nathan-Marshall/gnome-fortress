#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "gnome_fortress/model/BasicMeshNode.h"
#include "gnome_fortress/resource/ResourceManager.h"

namespace gnome_fortress {
namespace game {


class Wall : public model::BasicMeshNode {

public:
    Wall(   resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            float wallHealth = 100);

protected:
    void onUpdateSelf(float dt) override;

private:
    float health;
};


}
}