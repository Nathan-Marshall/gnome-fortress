#pragma once

#include "gnome_fortress/camera/Camera.h"
#include "gnome_fortress/model/SceneNode.h"

namespace gnome_fortress {
namespace camera {

// This Camera contains a specialized SceneNode that updates that camera's view matrix every frame
class SceneNodeCamera : public Camera {
public:
    SceneNodeCamera();

    // Returns the SceneNode that updates the camera's view matrix with its global transform, whenever the node's update happens
    model::SceneNode *getNode();

private:
    class CameraUpdaterNode : public model::SceneNode {
    public:
        CameraUpdaterNode(SceneNodeCamera *camera);

        virtual void onUpdateSelf(float delta_time) override;
    private:
        SceneNodeCamera *camera;
    };

    CameraUpdaterNode node;
};

}
}