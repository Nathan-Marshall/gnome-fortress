#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "gnome_fortress/model/BasicMeshGroupNode.h"
#include "gnome_fortress/resource/ResourceManager.h"

namespace gnome_fortress {
namespace game {


class Wall : public model::BasicMeshGroupNode {

public:
    Wall(   resource::ResourceManager &resourceManager,
            renderer::BasicMeshNodeTechnique *technique,
            float wallHealth = 100);

    void SetDimensions(float l, float h, float w);
    float GetLength();
    float GetHeight();
    float GetWidth();

    void DoDamage(float d);

    float GetHealth();

protected:
    void onUpdateSelf(float dt) override;

private:
    float health;
    float length;
    float height;
    float width;
};


}
}