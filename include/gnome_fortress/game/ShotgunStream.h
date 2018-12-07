#pragma once

#include "gnome_fortress/game/ShotgunStreamTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/PointSet.h"

namespace gnome_fortress {
namespace game {

class ShotgunStream : public model::SceneNode {
public:
    ShotgunStream(const model::Texture *texture, ShotgunStreamTechnique *technique);
    ~ShotgunStream();

    void onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const override;

    const model::PointSet *getPointSet() const;

    ShotgunStreamTechnique *getTechnique() const;

    void setPower(float power);

private:
    //Create particles for the shotgun stream effect
    static model::PointSet *CreateConeParticles(int num_particles);

    //Point set, texture, and technique to use for rendering this particle effect
    const model::PointSet *pointSet;
    const model::Texture *texture;
    ShotgunStreamTechnique *technique;

    float power;
};

}
}