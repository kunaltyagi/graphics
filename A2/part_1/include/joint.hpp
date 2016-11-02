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
    Pose() {}
    Pose(Point t, Point r): T(t), R(r) {}
    Point T = {0, 0, 0, 1}, R = {0, 0, 1, 0};  // T: translation, R: rotation
    // translation.w = 1, rotation in quaternion
};  // class Pose

struct ObjectBase
{
    virtual void draw(void) = 0;
    virtual void load(void) {};
    virtual ~ObjectBase() {}
    virtual void input(int) {}
  protected:
    Point _origin = {0, 0, 0, 1};
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
    Pose _offset;
    virtual void _tf()
    {
        glRotatef(_offset.R.w, _offset.R.x, _offset.R.y, _offset.R.z);
        glTranslatef(_offset.T.x, _offset.T.y, _offset.T.z);
    }
public:
    void replaceChild(ObjectPtr newChild_) { _child = newChild_; }
    void replaceParent(ObjectPtr newParent_) { _parent = newParent_; }
    void setAxis(Vector axis_) { _jointAxis = axis_; }
    void manipulate(float delta_) { _jointActuation += delta_; }
    float getActuation() { return _jointActuation; }
    Vector getAxis() { return _jointAxis; }
    void setOffset(Pose pose_) { _offset = pose_; }
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
        Joint::_tf();
    }
};

class TranslateJoint: public Joint
{
    void _tf()
    {
        Vector axis = _jointAxis * _jointActuation;
        glTranslatef(axis.x, axis.y, axis.z);
        Joint::_tf();
    }
};

#endif  // _JOINT_HPP_
