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

    //Draw the purple stream
    void onDrawSelf(const glm::mat4 &parent_transform, unsigned int pass) const override;

    const model::PointSet *getPointSet() const;

    PurpleRocketStreamTechnique *getTechnique() const;

    //Set the stream power for this effect
    void setPower(float power);

private:
    static model::PointSet *CreateConeParticles(int num_particles);

    //The point set, texture, and technique to be used for rendering this effect
    const model::PointSet *pointSet;
    const model::Texture *texture;
    PurpleRocketStreamTechnique *technique;

    float power;
};

}
}