#ifndef _JOINT_HPP_
#define _JOINT_HPP_

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>

#include <memory>

#include <glut/glut_framework.hpp>

using Point = glut_framework::Point<float>;

struct Pose
{
    Point T, R;  // T: translation, R: rotation
    // translation.w = 1, rotation in quaternion
};  // class Pose

struct ObjectBase
{
    virtual void draw(void) = 0;
    virtual void load(void) {};
};  // class ObjectBase
using ObjectPtr = std::shared_ptr<ObjectBase>;
using WeakObjPtr = std::weak_ptr<ObjectBase>;

class Joint: public ObjectBase
{
protected:
    ObjectPtr _child;
    WeakObjPtr _parent;
    Pose _jointPose;
public:
    void replaceChild(ObjectPtr newChild_) { _child = newChild_; }
    void replaceParent(ObjectPtr newParent_);
    virtual void manipulate(Pose deltaPose_) = 0;
    Pose getPose() { return _jointPose; }
    void draw(void) { /*transfor*/ _child->draw(); }
    void load(void) { _child->load(); }
};  // class Joint
using JointPtr = std::shared_ptr<Joint>;

#endif  // _JOINT_HPP_
