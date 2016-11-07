#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include <cmath>

#include <generic_object.hpp>
#include <front_handle.hpp>

struct Frame: public GenericObject
{
    void setupObject(void)
    {
        horizontalBar.setupObject();
        triangle_1.setupObject();
        triangle_2.setupObject();
        rearWheelBar.setupObject();
        rearWheelBar.setOrigin({0, 0, rearWheelBar.height});
        GenericObject::setupObject();
    }

    void setupMaterial(void)
    {
        horizontalBar.setupMaterial();
        triangle_1.setupMaterial();
        triangle_2.setupMaterial();
        rearWheelBar.setupMaterial();
    }

    void drawObject()
    {
        float triangle_offset_y = 2.5;
        float triangle_offset_x = (std::sin(deg2rad(45))*triangle_1.height/2 +  triangle_offset_y)*std::tan(deg2rad(frontWheel.angle));
        glPushMatrix();
        glTranslatef(std::sin(deg2rad(45))*triangle_1.height/2 + triangle_offset_x, triangle_offset_y, 0);
        triangle_1.draw();
        glTranslatef(std::sin(deg2rad(45))*(triangle_1.height + triangle_2.height)/2, 0, 0);
        glTranslatef(0, triangle_1.base_radius, 0); //triangle_1.base_radius, 0);
        triangle_2.draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(_jointVec[1]->getOrigin().x, 0, 0);
        glRotatef(-90 + frontWheel.angle, 0, 0, 1);
        rearWheelBar.draw();
        glPopMatrix();

        glRotatef(-1, 0, 0, 1);
        horizontalBar.draw();
    }

    void input(int key)
    {
        float forward = 0;
        float turn = 0;
        switch(key)
        {
        case '1': forward = 2; break;
        case '2': forward = -2; break;
        case '3': turn = 2; break;
        case '4': turn = -2; break;
        }
        _jointVec[1]->manipulate(forward);
        frontWheel.tireAxleJoint->manipulate(forward);
        _jointVec[0]->manipulate(turn);
    }

    FrontHandle frontWheel;
    Wheel rearWheel;
    Cylinder horizontalBar, triangle_1, triangle_2, rearWheelBar;
    float handleBarHeight = 5;
    Frame(): GenericObject()
    {
        _jointVec.push_back(std::make_shared<RevoluteJoint>());
        _jointVec[0]->replaceChild(std::make_shared<FrontHandle>(frontWheel));
        _jointVec[0]->setAxis({0, 1, 0});

        _jointVec.push_back(std::make_shared<RevoluteJoint>());
        _jointVec[1]->replaceChild(std::make_shared<Wheel>(rearWheel));
        _jointVec[1]->setAxis({0, 0, 1});
        float distance = rearWheel.radius*3.5;
        _jointVec[1]->setOrigin({distance, 0, 0, 1});

        horizontalBar.base_radius = 0.2;
        horizontalBar.top_radius = 0.2;
        horizontalBar.height = distance * 0.7;
        Pose pose;
        pose.R = {0, 1, 0, 90};
        pose.T = {0, handleBarHeight, horizontalBar.height/2 +
                        handleBarHeight*std::tan(deg2rad(frontWheel.angle)), 1};
        horizontalBar.setPose(pose);

        triangle_1.height = 6;
        triangle_1.base_radius = 0.2;
        triangle_1.top_radius = 0.2;
        pose.R = {1, 1, 0, 90};
        pose.T = {0, 0, 0, 1};
        triangle_1.setPose(pose);
        triangle_2.height = 6;
        triangle_2.base_radius = 0.2;
        triangle_2.top_radius = 0.2;
        pose.R = {1, -1, 0, 90};
        pose.T = {0, 0, 0, 1};
        triangle_2.setPose(pose);

        rearWheelBar.base_radius = 0.2;
        rearWheelBar.top_radius = 0.2;
        rearWheelBar.height = 5;
        pose.R = {0, 1, 0, 90};
        pose.T = Point();
        rearWheelBar.setPose(pose);

        color.x = color.y = color.z = 0.9;
        color.w = 1.0;
    }
};  // class Frame

#endif  // _FRAME_HPP_

