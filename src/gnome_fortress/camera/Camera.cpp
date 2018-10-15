#include "gnome_fortress/camera/Camera.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gnome_fortress {
namespace camera {

Camera::Camera(
        const glm::mat4 &view,
        float in_fov,
        float near,
        float far,
        float w,
        float h)
    : view(view),
      fov(in_fov),
      near_clip(near),
      far_clip(far),
      viewport_width(w),
      viewport_height(h) {
    updateProjection();
}

glm::mat4 Camera::getView() const {
    return view;
}

glm::mat4 Camera::getProjection() const {
    return projection;
}

void Camera::setProjection(float in_fov, float near, float far, float w, float h) {
    fov = in_fov;
    near_clip = near;
    far_clip = far;
    viewport_width = w;
    viewport_height = h;

    updateProjection();
}

void Camera::setFOV(float in_fov) {
    fov = in_fov;

    updateProjection();
}

void Camera::setNearClip(float near) {
    near_clip = near;

    updateProjection();
}

void Camera::setFarClip(float far) {
    far_clip = far;

    updateProjection();
}

void Camera::setViewport(float w, float h) {
    viewport_width = w;
    viewport_height = h;

    updateProjection();
}

void Camera::setView(const glm::mat4 &new_view) {
    view = new_view;
}

void Camera::updateProjection() {
    float top = tan(glm::radians(fov / 2))*near_clip;
    float right = top * viewport_width / viewport_height;
    projection = glm::frustum(-right, right, -top, top, near_clip, far_clip);
}

}
}