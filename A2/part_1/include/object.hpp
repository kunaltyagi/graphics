#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <joint.hpp>

struct Object: public ObjectBase
{
    virtual ~Object() { _cleanup(); }
    virtual void draw(void) { _drawJoints(); }
    void setPose(Pose newPose_) { _objPose = newPose_; }
    Pose getPose() { return _objPose; }
    void addJoint(JointPtr newJoint_) { _jointVec.push_back(newJoint_); }
    virtual void load() {}
protected:
    Pose _objPose;
    std::vector<JointPtr> _jointVec;
    void _drawJoints(void)
    {
        for (auto& item: _jointVec)
        {
            item->draw();
        }
    }
    virtual void _cleanup() {}
};  // class Object

#endif  // _OBJECT_HPP_
