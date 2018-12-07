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

    //Set the dimensions of this wall
    void SetDimensions(float l, float h, float w);

    //Get the dimensions of this wall
    float GetLength();
    float GetHeight();
    float GetWidth();

    //Do damage to this wall
    void DoDamage(float d);

    //Get the current health of the wall
    float GetHealth();

protected:
    void onUpdateSelf(float dt) override;

private:
    //The health of a wall
    float health;

    //Dimensions of the wall
    float length;
    float height;
    float width;
};


}
}