#pragma once

#include "gnome_fortress/game/PrimitiveMeshes.h"
#include "gnome_fortress/model/BasicMeshNode.h"
#include "gnome_fortress/model/Mesh.h"

namespace gnome_fortress {
namespace game {

class Turret : public model::BasicMeshNode {
public:
    Turret(
        const model::Mesh *cube_mesh,
        const model::Mesh *cylinder_mesh,
        renderer::BasicProjectionTechnique *technique);

    ~Turret();

    void update(float delta_time) override;

private:
    float total_time;

    // basic turret
    model::BasicMeshNode *base;
    model::SceneNode *turret_top;
    model::BasicMeshNode *turret_top_cylinder;
    model::BasicMeshNode *shaft;
    model::BasicMeshNode *shaft_extension;

    // arm
    model::SceneNode *arm_segment_1;
    model::BasicMeshNode *arm_segment_1_cylinder;
    model::BasicMeshNode *arm_joint_cylinder;
    model::SceneNode *arm_segment_2;
    model::BasicMeshNode *arm_segment_2_cylinder;

    // hand
    model::SceneNode *hand;
    model::BasicMeshNode *hand_joint_cylinder;

    // finger 1
    model::SceneNode *finger_1_segment_1;
    model::BasicMeshNode *finger_1_segment_1_cylinder;
    model::BasicMeshNode *finger_1_joint_cylinder;
    model::BasicMeshNode *finger_1_segment_2;

    // finger 2
    model::SceneNode *finger_2_segment_1;
    model::BasicMeshNode *finger_2_segment_1_cylinder;
    model::BasicMeshNode *finger_2_joint_cylinder;
    model::BasicMeshNode *finger_2_segment_2;
};

}
}