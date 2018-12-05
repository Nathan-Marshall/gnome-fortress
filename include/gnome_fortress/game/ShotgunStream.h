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
    static model::PointSet *CreateConeParticles(int num_particles);

    const model::PointSet *pointSet;
    const model::Texture *texture;
    ShotgunStreamTechnique *technique;

    float power;
};

}
}