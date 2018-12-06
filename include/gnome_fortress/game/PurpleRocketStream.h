#pragma once

#include "gnome_fortress/game/PurpleRocketStreamTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/PointSet.h"

namespace gnome_fortress {
namespace game {

class PurpleRocketStream : public model::SceneNode {
public:
    PurpleRocketStream(const model::Texture *texture, PurpleRocketStreamTechnique *technique);
    ~PurpleRocketStream();

    void onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const override;

    const model::PointSet *getPointSet() const;

    PurpleRocketStreamTechnique *getTechnique() const;

    void setPower(float power);

private:
    static model::PointSet *CreateConeParticles(int num_particles);

    const model::PointSet *pointSet;
    const model::Texture *texture;
    PurpleRocketStreamTechnique *technique;

    float power;
};

}
}