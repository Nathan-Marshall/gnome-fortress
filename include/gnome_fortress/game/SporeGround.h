#pragma once

#include "gnome_fortress/game/SporeGroundTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/PointSet.h"

namespace gnome_fortress {
namespace game {

class SporeGround : public model::SceneNode {
public:
    SporeGround(const model::Texture *texture, SporeGroundTechnique *technique);
    ~SporeGround();

    void onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const override;
    void onUpdateSelf(float delta_time) override;
    const model::PointSet *getPointSet() const;

    SporeGroundTechnique *getTechnique() const;

    void setPower(float power);

private:
    static model::PointSet *CreateSphericalParticles(int num_particles);

    const model::PointSet *pointSet;
    const model::Texture *texture;
    SporeGroundTechnique *technique;

    float power;

    float timer;
};

}
}