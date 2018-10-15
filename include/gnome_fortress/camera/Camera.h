#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace gnome_fortress {
namespace camera {

/* This class is inteded to generate and store a projection matrix. It is also intended to store a view matrix,
 * but subclasses should manage updating the view matrix, since various custom movement models may be desired. */
class Camera {
public:
    Camera(const glm::mat4 &view = {},
            float fov = 60,
            float near_clip = 0.01f,
            float far_clip = 1000,
            float width = 960,
            float height = 540);

    // === VIEW ===

    // Returns the view matrix
    virtual glm::mat4 getView() const;

    // === PROJECTION ===

    // Returns the projection matrix
    glm::mat4 getProjection() const;

    // set all the values involved in creating a projection matrix, and update the projection matrix
    void setProjection(float fov, float near_clip, float far_clip, float width, float height);

    // set field of view and update the projection matrix
    void setFOV(float fov);

    // set near clipping distance and update the projection matrix
    void setNearClip(float near_clip);

    // set far clipping distance and update the projection matrix
    void setFarClip(float far_clip);

    // set viewport width and height and update the projection matrix
    void setViewport(float width, float height);

protected:
    // set the view matrix
    void setView(const glm::mat4 &new_view);

private:
    // === VIEW ===

    // The view matrix should only be updated by subclasses of Camera
    glm::mat4 view;

    // === PROJECTION ===

    // This should be called after any change to near_clip, far_clip, fov, viewport_width, or viewport_height.
    void updateProjection();

    /* Projection matrix, created from near_clip, far_clip, fov, viewport_width, and viewport_height.
     * If modifying any of those values, this matrix should be updated as well. */
    glm::mat4 projection;

    // near clipping plane distance
    float near_clip;
    // far clipping plane distance
    float far_clip;
    // field of view
    float fov;
    // viewport width
    float viewport_width;
    // viewport height
    float viewport_height;
};

}
}