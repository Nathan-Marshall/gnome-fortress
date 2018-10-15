#include "gnome_fortress/game/Turret.h"

namespace gnome_fortress {
namespace game {

using namespace gnome_fortress::model;
float pi = glm::pi<float>();

Turret::Turret(
        const Mesh *cube_mesh,
        const Mesh *cylinder_mesh,
        renderer::BasicProjectionTechnique *technique)
    : BasicMeshNode(nullptr, technique),
      total_time(0) {

    // basic turret
    base = new BasicMeshNode(cube_mesh, getTechnique());
    base->setPosition(0.0f, 0.5f, 0.0f);
    base->setScale(0.4f, 1.0f, 0.4f);
    appendChild(base);

    turret_top = new SceneNode();
    turret_top->setPosition(0.0f, 1.0f, 0.0f);
    appendChild(turret_top);

    turret_top_cylinder = new BasicMeshNode(cylinder_mesh, getTechnique());
    turret_top_cylinder->setScale(0.8f, 0.3f, 0.8f);
    turret_top->appendChild(turret_top_cylinder);

    shaft = new BasicMeshNode(cylinder_mesh, getTechnique());
    shaft->setOrbit(-pi / 2, glm::vec3(0, 0, 1), glm::vec3(0.3f, 0.0f, 0.0f), glm::vec3(0.3f, 0.2f, 0.0f));
    shaft->setScale(0.2f, 0.4f, 0.2f);
    turret_top->appendChild(shaft);

    shaft_extension = new BasicMeshNode(cylinder_mesh, getTechnique());
    shaft_extension->setPosition(0.0f, 1.0f, 0.0f);
    shaft_extension->setScale(0.5f, 2.0f, 0.5f);
    shaft->appendChild(shaft_extension);

    // arm
    arm_segment_1 = new SceneNode();
    arm_segment_1->setPosition(0.0f, 0.5f, 0.0f);
    arm_segment_1->setRotation(pi * 0.4f, glm::vec3(1, 0, 0));
    appendChild(arm_segment_1);

    arm_segment_1_cylinder = new BasicMeshNode(cylinder_mesh, getTechnique());
    arm_segment_1_cylinder->setPosition(0.0f, 0.3f, 0.0f);
    arm_segment_1_cylinder->setScale(0.1f, 0.6f, 0.1f);
    arm_segment_1->appendChild(arm_segment_1_cylinder);

    arm_joint_cylinder = new BasicMeshNode(cylinder_mesh, getTechnique());
    arm_joint_cylinder->setPosition(0.0f, 0.6f, 0.0f);
    arm_joint_cylinder->setRotation(-pi / 2, glm::vec3(0, 0, 1));
    arm_joint_cylinder->setScale(0.15f, 0.1f, 0.15f);
    arm_segment_1->appendChild(arm_joint_cylinder);

    arm_segment_2 = new SceneNode();
    arm_segment_2->setPosition(0.0f, 0.6f, 0.0f);
    arm_segment_2->setRotation(pi * 0.4f, glm::vec3(1, 0, 0));
    arm_segment_1->appendChild(arm_segment_2);

    arm_segment_2_cylinder = new BasicMeshNode(cylinder_mesh, getTechnique());
    arm_segment_2_cylinder->setPosition(0.0f, 0.3f, 0.0f);
    arm_segment_2_cylinder->setScale(0.1f, 0.6f, 0.1f);
    arm_segment_2->appendChild(arm_segment_2_cylinder);

    // hand
    hand = new SceneNode();
    hand->setPosition(0.0f, 0.6f, 0.0f);
    arm_segment_2->appendChild(hand);

    hand_joint_cylinder = new BasicMeshNode(cylinder_mesh, getTechnique());
    hand_joint_cylinder->setRotation(-pi / 2, glm::vec3(0, 0, 1));
    hand_joint_cylinder->setScale(0.15f, 0.1f, 0.15f);
    hand->appendChild(hand_joint_cylinder);

    // finger 1
    finger_1_segment_1 = new SceneNode();
    finger_1_segment_1->setRotation(pi * -0.4f, glm::vec3(1, 0, 0));
    hand->appendChild(finger_1_segment_1);

    finger_1_segment_1_cylinder = new BasicMeshNode(cylinder_mesh, getTechnique());
    finger_1_segment_1_cylinder->setPosition(0.0f, 0.15f, 0.0f);
    finger_1_segment_1_cylinder->setScale(0.05f, 0.3f, 0.05f);
    finger_1_segment_1->appendChild(finger_1_segment_1_cylinder);

    finger_1_joint_cylinder = new BasicMeshNode(cylinder_mesh, getTechnique());
    finger_1_joint_cylinder->setPosition(0.0f, 0.3f, 0.0f);
    finger_1_joint_cylinder->setRotation(-pi / 2, glm::vec3(0, 0, 1));
    finger_1_joint_cylinder->setScale(0.075f, 0.05f, 0.075f);
    finger_1_segment_1->appendChild(finger_1_joint_cylinder);

    finger_1_segment_2 = new BasicMeshNode(cylinder_mesh, getTechnique());
    finger_1_segment_2->setOrbit(pi * 0.4f, glm::vec3(1, 0, 0), glm::vec3(0.0f, 0.3f, 0.0f), glm::vec3(0.0f, 0.425f, 0.0f));
    finger_1_segment_2->setScale(0.05f, 0.25f, 0.05f);
    finger_1_segment_1->appendChild(finger_1_segment_2);

    // finger 2
    finger_2_segment_1 = new SceneNode();
    finger_2_segment_1->setRotation(pi * 0.4f, glm::vec3(1, 0, 0));
    hand->appendChild(finger_2_segment_1);

    finger_2_segment_1_cylinder = new BasicMeshNode(cylinder_mesh, getTechnique());
    finger_2_segment_1_cylinder->setPosition(0.0f, 0.15f, 0.0f);
    finger_2_segment_1_cylinder->setScale(0.05f, 0.3f, 0.05f);
    finger_2_segment_1->appendChild(finger_2_segment_1_cylinder);

    finger_2_joint_cylinder = new BasicMeshNode(cylinder_mesh, getTechnique());
    finger_2_joint_cylinder->setPosition(0.0f, 0.3f, 0.0f);
    finger_2_joint_cylinder->setRotation(-pi / 2, glm::vec3(0, 0, 1));
    finger_2_joint_cylinder->setScale(0.075f, 0.05f, 0.075f);
    finger_2_segment_1->appendChild(finger_2_joint_cylinder);

    finger_2_segment_2 = new BasicMeshNode(cylinder_mesh, getTechnique());
    finger_2_segment_2->setOrbit(pi * -0.4f, glm::vec3(1, 0, 0), glm::vec3(0.0f, 0.3f, 0.0f), glm::vec3(0.0f, 0.425f, 0.0f));
    finger_2_segment_2->setScale(0.05f, 0.25f, 0.05f);
    finger_2_segment_1->appendChild(finger_2_segment_2);
}

Turret::~Turret() {
    // basic turret
    delete base;
    delete turret_top;
    delete turret_top_cylinder;
    delete shaft;
    delete shaft_extension;

    // arm
    delete arm_segment_1;
    delete arm_segment_1_cylinder;
    delete arm_joint_cylinder;
    delete arm_segment_2;
    delete arm_segment_2_cylinder;

    // hand
    delete hand;
    delete hand_joint_cylinder;

    // finger 1
    delete finger_1_segment_1;
    delete finger_1_segment_1_cylinder;
    delete finger_1_joint_cylinder;
    delete finger_1_segment_2;

    // finger 2
    delete finger_2_segment_1;
    delete finger_2_segment_1_cylinder;
    delete finger_2_joint_cylinder;
    delete finger_2_segment_2;
}

void Turret::update(float delta_time) {
    total_time += delta_time;

    // basic turret
    turret_top->rotate(delta_time / 10 * 2 * pi, glm::vec3(0, 1, 0));

    shaft->setOrbit(glm::sin(total_time / 4 * pi * 2) * pi / 6 - pi / 2, glm::vec3(0, 0, 1), glm::vec3(0.3f, 0.0f, 0.0f), glm::vec3(0.3f, 0.2f, 0.0f));

    shaft_extension->setY(1.0f - 0.5f * glm::abs(glm::cos(total_time * pi * 2)));

    // arm
    arm_segment_1->rotate(delta_time / 10 * 2 * pi, glm::vec3(0, 1, glm::cos(0.4 * pi)));

    arm_segment_2->setRotation(glm::sin(total_time / 4 * pi * 2) * pi * 0.4f, glm::vec3(1, 0, 0));

    // hand and fingers
    hand->rotate(delta_time / 3 * -2 * pi, glm::vec3(0, 1, 0));

    finger_1_segment_1->setRotation(glm::sin(total_time * pi * 2) * pi * 0.2f - pi * 0.4f, glm::vec3(1, 0, 0));
    finger_2_segment_1->setRotation(glm::sin(total_time * pi * 2) * pi * -0.2f + pi * 0.4f, glm::vec3(1, 0, 0));
}

}
}