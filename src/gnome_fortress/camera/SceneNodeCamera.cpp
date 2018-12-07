#include "gnome_fortress/camera/SceneNodeCamera.h"

#include <iostream>

namespace gnome_fortress {
namespace camera {

SceneNodeCamera::SceneNodeCamera()
    : node(this) {

}

model::SceneNode *SceneNodeCamera::getNode() {
    return &node;
}

SceneNodeCamera::CameraUpdaterNode::CameraUpdaterNode(SceneNodeCamera *camera)
    : camera(camera) {

}

//Update the camera view matrix based on the current transformations of the camera node
void SceneNodeCamera::CameraUpdaterNode::onUpdateSelf(float delta_time) {
    glm::mat4 transform = getGlobalInverseTransform();

    glm::vec4 position = transform * glm::vec4(0, 0, 0, 1);
    glm::vec4 right   = glm::normalize(transform * glm::vec4( 1,  0,  0,  0));
    glm::vec4 up      = glm::normalize(transform * glm::vec4( 0,  1,  0,  0));
    glm::vec4 forward = glm::normalize(transform * glm::vec4( 0,  0,  1,  0));

    camera->setView(glm::mat4(right, up, forward, glm::vec4(position.x, position.y, position.z, 1)));
}

}
}