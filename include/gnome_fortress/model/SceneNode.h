#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/quaternion.hpp>

#include <functional>
#include <vector>

namespace gnome_fortress {
namespace model {

class SceneNode {
public:
    SceneNode();

    // updates this node and all its children
    virtual void update(float delta_time);

    // draws this node and all its children, applying the local transformation
    virtual void draw(const glm::mat4 &parent_transform) const;

	//GLOBAL SCENE BOUNDS
	const static float XBOUND_POS;
	const static float XBOUND_NEG;

	const static float YBOUND_POS;
	const static float YBOUND_NEG;

	const static float ZBOUND_POS;
	const static float ZBOUND_NEG;


    // === LOCAL TRANSFORMATIONS ===

    // Returns the local position
    glm::vec3 getPosition() const;

    // Sets the local position
    void setPosition(const glm::vec3 &new_position);

    // Sets the local position
    void setPosition(float x, float y, float z);

    // Sets the local position x
    void setX(float x);

    // Sets the local position y
    void setY(float y);

    // Sets the local position z
    void setZ(float z);

    // Applies a translation to the local position
    void translate(const glm::vec3 &translation);

    // Applies a translation to the local position
    void translate(float tx, float ty, float tz);

    // Applies a translation to the local position x
    void translateX(float tx);

    // Applies a translation to the local position y
    void translateY(float ty);

    // Applies a translation to the local position z
    void translateZ(float tz);

    // Returns the local rotation quaternion
    glm::quat getRotation() const;

    // Creates and returns a rotation matrix from the local rotation quaternion
    glm::mat4 getRotationMatrix() const;

    // Sets the local rotation
    void setRotation(const glm::quat &new_rotation);

    // Sets the local rotation
    void setRotation(float angle, const glm::vec3 &axis);

    // Applies a rotation to the local rotation
    void rotate(const glm::quat &rotation);

    // Applies a rotation to the local rotation
    void rotate(float angle, const glm::vec3 &axis);

    /* Sets initial position from and rotation around an arbitrary point in parent space, affecting both the
     * local rotation and local position values */
    void setOrbit(const glm::quat &rotation, const glm::vec3 &anchor, const glm::vec3 &init_position);

    /* Sets initial position from and rotation around an arbitrary point in parent space, affecting both the
     * local rotation and local position values */
    void setOrbit(float angle, const glm::vec3 &axis, const glm::vec3 &anchor, const glm::vec3 &init_position);

    /* Rotates around an arbitrary point in parent space, affecting both the
     * local rotation and local position values */
    void orbit(const glm::quat &rotation, const glm::vec3 &anchor);

    /* Rotates around an arbitrary point in parent space, affecting both the
     * local rotation and local position values */
    void orbit(float angle, const glm::vec3 &axis, const glm::vec3 &anchor);

    // Returns the local scale
    glm::vec3 getScale() const;

    // Sets the local scale
    void setScale(const glm::vec3 &new_scale);

    // Sets the local scale
    void setScale(float sx, float sy, float sz);

    // Sets the local scale x, y, and z to the same value
    void setScale(float sxyz);

    // Sets the local scale x
    void setScaleX(float sx);

    // Sets the local scale y
    void setScaleY(float sy);

    // Sets the local scale z
    void setScaleZ(float sz);

    // Multiplies the local scale by the given scale values
    void scale(const glm::vec3 &scale);

    // Multiplies the local scale by the given scale values
    void scale(float sx, float sy, float sz);

    // Multiplies the local scale x, y, and z by the given scale value
    void scale(float sxyz);

    // Multiplies the local scale x by the given scale x
    void scaleX(float sx);

    // Multiplies the local scale y by the given scale y
    void scaleY(float sy);

    // Multiplies the local scale z by the given scale z
    void scaleZ(float sz);

    // Composes the local position, rotation, and scale in SRT ordering into a single 4x4 matrix
    glm::mat4 getTransformMatrix() const;

    // Resets local position, rotation, and scale values
    void resetTransform();

    // === ANCESTRY ===

    // Returns the parent node
    SceneNode *getParent() const;

    // Composes the local transform matrix with all ancestor transform matrices.
    glm::mat4 getGlobalTransform() const;

    // Composes the inverse local transform matrix with all ancestor inverse transform matrices.
    glm::mat4 getGlobalInverseTransform() const;

    // === CHILD MANAGEMENT ===

    int getNumChildren() const;

    // Returns the index of the given child, or -1 if the given node is not a child
    int indexOf(SceneNode *child) const;

    // Returns the child at the given index
    SceneNode *getChild(int index) const;

    // Calls the given callback for each child
    void forEachChild(const std::function<void(SceneNode *)> &callback) const;

    // Inserts a child at the given index
    void insertChild(SceneNode *child, int index);

    // Appends a child to the back of the list
    void appendChild(SceneNode *child);

    // Replaces the child at the given index
    void replaceChild(SceneNode *child, int index);

    // Removes the child at the given index
    void removeChild(int index);

    // Removes all children
    void clearChildren();

    /* Tells the parent remove this node from its children.
     * This is not particularily fast because the parent must first search for this node. */
    void removeFromParent();

protected:
    // Uses the gl functions to transform the top of the matrix stack by the local transformations
    void applyTransform() const;

    // instructions for what to do when updating self (does not include drawing children)
    virtual void onUpdateSelf(float delta_time);

    // instructions for what to do when updating children
    virtual void onUpdateChildren(float delta_time);

    // instructions for what to do when drawing self, after applying transformations (does not include drawing children)
    virtual void onDrawSelf(const glm::mat4 &parent_transform) const;

    // instructions for what to do when drawing children, after applying transformations
    virtual void onDrawChildren(const glm::mat4 &parent_transform) const;

private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale_vec;

    SceneNode *parent;
    std::vector<SceneNode *> children;
};

}
}