#pragma once

#include "gnome_fortress/game/RocketGroundTechnique.h"
#include "gnome_fortress/model/SceneNode.h"
#include "gnome_fortress/model/PointSet.h"

namespace gnome_fortress {
namespace game {

class RocketGround : public model::SceneNode {
public:
    RocketGround(const model::Texture *texture, RocketGroundTechnique *technique);
    ~RocketGround();

    void onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const override;
    void onUpdateSelf(float delta_time) override;

    const model::PointSet *getPointSet() const;

    RocketGroundTechnique *getTechnique() const;

    void setPower(float power);

private:
    static model::PointSet *CreateSphereParticles(int num_particles);

    //The point set, texture, and technique used for rendering this effect
    const model::PointSet *pointSet;
    const model::Texture *texture;
    RocketGroundTechnique *technique;

    float power;
    float timer;
};

}
}