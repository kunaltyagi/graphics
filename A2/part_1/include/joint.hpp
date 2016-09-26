#ifndef _JOINT_HPP_
#define _JOINT_HPP_

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>

#include <memory>

#include <glut/glut_framework.hpp>
#include <glut/vector.hpp>

using Point = glut_framework::Point<float>;
using Vector = glut_framework::Vector<float>;

struct Pose
{
    Point T, R;  // T: translation, R: rotation
    // translation.w = 1, rotation in quaternion
};  // class Pose

struct ObjectBase
{
    virtual void draw(void) = 0;
    virtual void load(void) {};
    virtual ~ObjectBase() {}
};  // class ObjectBase
using ObjectPtr = std::shared_ptr<ObjectBase>;
using WeakObjPtr = std::weak_ptr<ObjectBase>;

class Joint: public ObjectBase
{
protected:
    ObjectPtr _child;
    WeakObjPtr _parent;
    float _jointActuation;
    Vector _jointAxis;
    virtual void _tf() {}
public:
    void replaceChild(ObjectPtr newChild_) { _child = newChild_; }
    void replaceParent(ObjectPtr newParent_);
    void setAxis(Vector axis_) { _jointAxis = axis_; }
    void manipulate(float delta_) { _jointActuation += delta_; }
    float getActuation() { return _jointActuation; }
    Vector getAxis() { return _jointAxis; }
    void draw(void)
    {
        glPushMatrix();
        _tf();
        _child->draw();
        glPopMatrix();
    }
    void load(void) { _child->load(); }
    virtual ~Joint() {}
};  // class Joint
using JointPtr = std::shared_ptr<Joint>;
using FixedJoint = Joint;

class RevoluteJoint: public Joint
{
    void _tf()
    {
        glRotatef(_jointActuation, _jointAxis.x, _jointAxis.y, _jointAxis.z);
    }
};

class TranslateJoint: public Joint
{
    void _tf()
    {
        Vector axis = _jointAxis * _jointActuation;
        glTranslatef(axis.x, axis.y, axis.z);
    }
};

#endif  // _JOINT_HPP_
