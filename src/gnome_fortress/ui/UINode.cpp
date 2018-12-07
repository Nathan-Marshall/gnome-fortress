#include "gnome_fortress/ui/UINode.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace gnome_fortress {
namespace ui {

// === PUBLIC ===

UINode::UINode()
    : position(),
      rotation(),
      scale_vec(1, 1),
      parent(nullptr),
      children(),
      enabled(true),
      visible(true) {
}

void UINode::update(float delta_time) {
    onUpdateSelf(delta_time);
    onUpdateChildren(delta_time);
}

void UINode::draw(const glm::mat3 &parent_transform, unsigned int pass/* = 0*/) const {
    onDrawSelf(parent_transform, pass);
    onDrawChildren(parent_transform, pass);
}

// === LOCAL TRANSFORMATIONS ===

glm::vec2 UINode::getPosition() const {
    return position;
}

void UINode::setPosition(const glm::vec2 &new_position) {
    position = new_position;
}

void UINode::setPosition(float x, float y) {
    position = glm::vec2(x, y);
}

void UINode::setX(float x) {
    position.x = x;
}

void UINode::setY(float y) {
    position.y = y;
}

void UINode::translate(const glm::vec2 &translation) {
    position += translation;
}

void UINode::translate(float tx, float ty) {
    translate(glm::vec2(tx, ty));
}

void UINode::translateX(float tx) {
    translate(glm::vec2(tx, 0));
}

void UINode::translateY(float ty) {
    translate(glm::vec2(0, ty));
}

float UINode::getRotation() const {
    return rotation;
}

void UINode::setRotation(float new_rotation) {
    rotation = new_rotation;
}

void UINode::rotate(float angle) {
    rotation += angle;
}

void UINode::setOrbit(float in_rotation, const glm::vec2 &anchor, const glm::vec2 &init_position) {
    setRotation(in_rotation);

    position = init_position - anchor;
    position = glm::vec2(rotation * glm::vec3(position, 0));
    position += anchor;
}

void UINode::orbit(float in_rotation, const glm::vec2 &anchor) {
    rotate(in_rotation);

    position -= anchor;
    position = glm::vec2(in_rotation * glm::vec3(position, 0));
    position += anchor;
}

glm::vec2 UINode::getScale() const {
    return scale_vec;
}

void UINode::setScale(const glm::vec2 &new_scale) {
    scale_vec = new_scale;
}

void UINode::setScale(float sx, float sy) {
    scale_vec = glm::vec2(sx, sy);
}

void UINode::setScale(float sxy) {
    scale_vec = glm::vec2(sxy, sxy);
}

void UINode::setScaleX(float sx) {
    scale_vec.x = sx;
}

void UINode::setScaleY(float sy) {
    scale_vec.y = sy;
}

void UINode::scale(const glm::vec2 &scale) {
    scale_vec *= scale;
}

void UINode::scale(float sx, float sy) {
    scale_vec *= glm::vec2(sx, sy);
}

void UINode::scale(float sxy) {
    scale_vec *= glm::vec2(sxy, sxy);
}

void UINode::scaleX(float sx) {
    scale_vec.x *= sx;
}

void UINode::scaleY(float sy) {
    scale_vec.y *= sy;
}

glm::mat3 UINode::getTransformMatrix() const {
    const glm::vec2 &t = position;
    float r = rotation;
    const glm::vec2 &s = scale_vec;

    // what look like rows here are actually columns
    glm::mat3 local_translation_mat(
        1, 0, 0,
        0, 1, 0,
        t.x, t.y, 1
    );

    // again, keep in mind that what look like rows here are actually columns
    glm::mat3 local_rotation_mat(
        glm::cos(r), glm::sin(r), 0,
        -glm::sin(r), glm::cos(r), 0,
        0, 0, 1
    );

    glm::mat3 local_scale_mat(
        s.x, 0, 0,
        0, s.y, 0,
        0, 0, 1
    );

    return local_translation_mat * local_rotation_mat * local_scale_mat;
}

void UINode::resetTransform() {
    position = glm::vec2();
    rotation = 0;
    scale_vec = glm::vec2(1, 1);
}

// === ANCESTRY ===

UINode *UINode::getParent() const {
    return parent;
}

glm::mat3 UINode::getGlobalTransform() const {
    if (parent) {
        return parent->getGlobalTransform() * getTransformMatrix();
    } else {
        return getTransformMatrix();
    }
}

glm::mat3 UINode::getGlobalInverseTransform() const {
    return glm::inverse(getGlobalTransform());
}

// === CHILD MANAGEMENT ===

int UINode::getNumChildren() const {
    return children.size();
}

int UINode::indexOf(UINode *child) const {
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            return i;
        }
    }
    return -1;
}

UINode *UINode::getChild(int index) const {
    if (index < 0 || index >= children.size()) {
        throw std::exception("Failed to get child. Index out of bounds.");
    }

    return children[index];
}

void UINode::forEachChild(const std::function<void(UINode *)> &callback) const {
    for (UINode *child : children) {
        callback(child);
    }
}

void UINode::insertChild(UINode *child, int index) {
    if (index < 0 || index > children.size()) {
        throw std::exception("Failed to insert child. Index out of bounds.");
    }
    if (child->parent) {
        throw std::exception("Failed to insert child. Given node already has a parent.");
    }

    children.insert(children.begin() + index, child);
    child->parent = this;
}

void UINode::appendChild(UINode *child) {
    if (child->parent) {
        throw std::exception("Failed to append child. Given node already has a parent.");
    }

    children.push_back(child);
    child->parent = this;
}

void UINode::replaceChild(UINode *child, int index) {
    if (index < 0 || index >= children.size()) {
        throw std::exception("Failed to replace child. Index out of bounds.");
    }
    if (child->parent) {
        throw std::exception("Failed to replace child. Given node already has a parent.");
    }

    children[index]->parent = nullptr;
    children[index] = child;
    child->parent = this;
}

void UINode::removeChild(int index) {
    if (index < 0 || index >= children.size()) {
        throw std::exception("Failed to remove child. Index out of bounds.");
    }

    children[index]->parent = nullptr;
    children.erase(children.begin() + index);
}

void UINode::clearChildren() {
    for (UINode *child : children) {
        child->parent = nullptr;
    }
    children.clear();
}

void UINode::removeFromParent() {
    if (parent) {
        parent->removeChild(parent->indexOf(this));
    }
}

bool UINode::isEnabled() const {
    return enabled;
}

void UINode::setEnabled(bool e) {
    enabled = e;
}

bool UINode::isVisibile() const {
    return visible;
}

void UINode::setVisible(bool v) {
    visible = v;
}

// === PROTECTED ===

void UINode::applyTransform() const {
    // SRT transform
    glTranslatef(position.x, position.y, 0);
    glRotatef(rotation, 0, 0, 1);
    glScalef(scale_vec.x, scale_vec.y, 0);
}

void UINode::onUpdateSelf(float delta_time) {
    // override to add update behaviour
}

void UINode::onUpdateChildren(float delta_time) {
    for (UINode *child : children) {
        if (child->enabled) {
            child->update(delta_time);
        }
    }
}

void UINode::onDrawSelf(const glm::mat3 &parent_transform, unsigned int pass) const {
    // override to add draw behaviour
}

void UINode::onDrawChildren(const glm::mat3 &parent_transform, unsigned int pass) const {
    for (UINode *child : children) {
        if (child->visible) {
            child->draw(parent_transform * getTransformMatrix(), pass);
        }
    }
}

}
}