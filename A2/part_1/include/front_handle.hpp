#ifndef _FRONT_HANDLE_HPP_
#define _FRONT_HANDLE_HPP_

#include <generic_object.hpp>
#include <wheel.hpp>

struct FrontHandle: public GenericObject
{
    void setupObject(void)
    {
        axle.setupObject();
        handlebar.setupObject();
        GenericObject::setupObject();
    }

    void setupMaterial(void)
    {
        axle.setupMaterial();
        handlebar.setupMaterial();
    }

    void drawObject()
    {
        glRotatef(-angle, 0, 0, 1);
        axle.draw();
        handlebar.draw();
    }

    Wheel tire;
    JointPtr tireAxleJoint;
    Cylinder axle, handlebar;
    float angle;
    FrontHandle(float angle_ = 20): GenericObject()
    {
        angle = angle_;

        tireAxleJoint = std::make_shared<RevoluteJoint>();
        _jointVec.push_back(tireAxleJoint);
        _jointVec[0]->replaceChild(std::make_shared<Wheel>(tire));
        _jointVec[0]->setAxis({0, 0, 1});

        Pose pose;
        axle.base_radius = 0.15;
        axle.top_radius = 0.15;
        axle.height = 2.*tire.radius;
        pose.R = {1, 0, 0, -90};
        pose.T.z = axle.height/2;
        axle.setPose(pose);
        axle.color = {0.5, 0.7, 0.7, 1};

        handlebar.base_radius = 0.15;
        handlebar.top_radius = 0.15;
        handlebar.height = axle.height;
        pose = Pose();
        pose.T.y = axle.height;
        handlebar.setPose(pose);
        handlebar.color = {0.5, 0.7, 0.7, 1};

        color.x = color.y = color.z = 0.9;
        color.w = 1.0;
    }
};  // class FrontHandle

#endif  // _FRONT_HANDLE_HPP_

