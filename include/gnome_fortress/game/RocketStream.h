#pragma once

#include "gnome_fortress/game/RocketStreamTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/PointSet.h"

namespace gnome_fortress {
namespace game {

class RocketStream : public model::SceneNode {
public:
    RocketStream(const model::Texture *texture, RocketStreamTechnique *technique);
    ~RocketStream();

    void onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const override;

    const model::PointSet *getPointSet() const;

    RocketStreamTechnique *getTechnique() const;

    void setPower(float power);

private:
    static model::PointSet *CreateConeParticles(int num_particles);

    const model::PointSet *pointSet;
    const model::Texture *texture;
    RocketStreamTechnique *technique;

    float power;
};

}
}