#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <joint.hpp>

struct Object: public ObjectBase
{
    Object() {}
    virtual ~Object() { _cleanup(); }
    virtual void draw(void) { _drawJoints(); }
    void setPose(Pose newPose_) { _objPose = newPose_; }
    Pose getPose() { return _objPose; }
    void addJoint(JointPtr newJoint_) { _jointVec.push_back(newJoint_); }
    virtual void load(void) 
    {
        for(auto& item: _jointVec)
        {
            item->load();
        }
    }
protected:
    Pose _objPose = Pose(Point(0, 0, 0, 1), Point(0, 0, 1, 0));
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
