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

    //Get the technique used by this effect
    SporeGroundTechnique *getTechnique() const;

    //Set the power for the effect
    void setPower(float power);

private:
    static model::PointSet *CreateSphericalParticles(int num_particles);

    //The point set, texture, and technique used to render this particle effect
    const model::PointSet *pointSet;
    const model::Texture *texture;
    SporeGroundTechnique *technique;

    float power;

    float timer;
};

}
}