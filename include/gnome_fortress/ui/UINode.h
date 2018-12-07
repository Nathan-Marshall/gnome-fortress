#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/quaternion.hpp>

#include <functional>
#include <vector>

namespace gnome_fortress {
namespace ui {

class UINode {
public:
    UINode();

    // updates this node and all its children
    virtual void update(float delta_time);

    /* Draws this node and all its children, applying the local transformation.
     * Nodes can perform different operations depending on the pass number. */
    virtual void draw(const glm::mat3 &parent_transform, unsigned int pass = 0) const;

    // === LOCAL TRANSFORMATIONS ===

    // Returns the local position
    glm::vec2 getPosition() const;

    // Sets the local position
    void setPosition(const glm::vec2 &new_position);

    // Sets the local position
    void setPosition(float x, float y);

    // Sets the local position x
    void setX(float x);

    // Sets the local position y
    void setY(float y);

    // Applies a translation to the local position
    void translate(const glm::vec2 &translation);

    // Applies a translation to the local position
    void translate(float tx, float ty);

    // Applies a translation to the local position x
    void translateX(float tx);

    // Applies a translation to the local position y
    void translateY(float ty);

    // Returns the local rotation quaternion
    float getRotation() const;

    // Sets the local rotation
    void setRotation(float angle);

    // Applies a rotation to the local rotation
    void rotate(float angle);

    /* Sets initial position from and rotation around an arbitrary point in parent space, affecting both the
     * local rotation and local position values */
    void setOrbit(float angle, const glm::vec2 &anchor, const glm::vec2 &init_position);

    /* Rotates around an arbitrary point in parent space, affecting both the
     * local rotation and local position values */
    void orbit(float angle, const glm::vec2 &anchor);

    // Returns the local scale
    glm::vec2 getScale() const;

    // Sets the local scale
    void setScale(const glm::vec2 &new_scale);

    // Sets the local scale
    void setScale(float sx, float sy);

    // Sets the local scale x and y to the same value
    void setScale(float sxy);

    // Sets the local scale x
    void setScaleX(float sx);

    // Sets the local scale y
    void setScaleY(float sy);

    // Multiplies the local scale by the given scale values
    void scale(const glm::vec2 &scale);

    // Multiplies the local scale by the given scale values
    void scale(float sx, float sy);

    // Multiplies the local scale x and y by the given scale value
    void scale(float sxy);

    // Multiplies the local scale x by the given scale x
    void scaleX(float sx);

    // Multiplies the local scale y by the given scale y
    void scaleY(float sy);

    // Composes the local position, rotation, and scale in SRT ordering into a single 4x4 matrix
    glm::mat3 getTransformMatrix() const;

    // Resets local position, rotation, and scale values
    void resetTransform();

    // === ANCESTRY ===

    // Returns the parent node
    UINode *getParent() const;

    // Composes the local transform matrix with all ancestor transform matrices.
    glm::mat3 getGlobalTransform() const;

    // Composes the inverse local transform matrix with all ancestor inverse transform matrices.
    glm::mat3 getGlobalInverseTransform() const;

    // === CHILD MANAGEMENT ===

    int getNumChildren() const;

    // Returns the index of the given child, or -1 if the given node is not a child
    int indexOf(UINode *child) const;

    // Returns the child at the given index
    UINode *getChild(int index) const;

    // Calls the given callback for each child
    void forEachChild(const std::function<void(UINode *)> &callback) const;

    // Inserts a child at the given index
    void insertChild(UINode *child, int index);

    // Appends a child to the back of the list
    void appendChild(UINode *child);

    // Replaces the child at the given index
    void replaceChild(UINode *child, int index);

    // Removes the child at the given index
    void removeChild(int index);

    // Removes all children
    void clearChildren();

    /* Tells the parent remove this node from its children.
     * This is not particularily fast because the parent must first search for this node. */
    void removeFromParent();

    // Nodes that are not enabled do not have their update function called
    bool isEnabled() const;
    // Nodes that are not enabled do not have their update function called
    void setEnabled(bool enabled);

    // Nodes that are not visible do not have their draw function called
    bool isVisibile() const;
    // Nodes that are not visible do not have their draw function called
    void setVisibile(bool visible);

protected:
    // Uses the gl functions to transform the top of the matrix stack by the local transformations
    void applyTransform() const;

    // instructions for what to do when updating self (does not include drawing children)
    virtual void onUpdateSelf(float delta_time);

    // instructions for what to do when updating children
    virtual void onUpdateChildren(float delta_time);

    // instructions for what to do when drawing self, after applying transformations (does not include drawing children)
    virtual void onDrawSelf(const glm::mat3 &parent_transform, unsigned int pass) const;

    // instructions for what to do when drawing children, after applying transformations
    virtual void onDrawChildren(const glm::mat3 &parent_transform, unsigned int pass) const;

private:
    glm::vec2 position;
    float rotation;
    glm::vec2 scale_vec;

    UINode *parent;
    std::vector<UINode *> children;

    bool enabled;
    bool visible;
};

}
}