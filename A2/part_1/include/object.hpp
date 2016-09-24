#include <cmath>
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>

#include <memory>

struct Pose
{
    Point transpose, rotation;  // transpose.w = 1, rotation in quaternion
};

struct ObjectBase
{
    virtual void draw(void) = 0;
};
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
};
using JointPtr = std::shared_ptr<Joint>;

struct Object: public ObjectBase
{
    virtual void draw(void) { _drawJoints(); }
    void setPose(Pose newPose_) { _objPose = newPose_; }
    Pose getPose() { return _objPose; }
    void addJoint(JointPtr newJoint_) { _jointVec.push_back(newJoint_); }
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
};

