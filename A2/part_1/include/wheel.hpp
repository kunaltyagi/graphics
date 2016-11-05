#ifndef _WHEEL_HPP_
#define _WHEEL_HPP_

#include <generic_object.hpp>
#include <cylinder.hpp>
#include <torus.hpp>

struct Wheel: public GenericObject
{
    void setupObject(void)
    {
        tire.rInner = thickness;
        tire.rOuter = radius;
        axle.base_radius = axle.top_radius = tire.rInner;
        axle.height = 3 * tire.rInner;

        tire.setupObject();
        axle.setupObject();
        for (auto& spoke : spokes)
        {
            spoke.height = tire.rOuter * 2;
            spoke.base_radius = spoke.top_radius = 0.05;
            spoke.setupObject();
        }
        _drawList = glGenLists(1);
        glNewList(_drawList, GL_COMPILE);
        glPushMatrix();
        drawObject();
        glPopMatrix();
        glEndList();
    }

    void setupMaterial(void)
    {
        tire.setupMaterial();
        axle.setupMaterial();
        for (auto& spoke : spokes)
        {
            spoke.setupMaterial();
        }
    }

    void drawObject()
    {
        tire.draw();
        axle.draw();
        // plane of spokes is different
        glRotatef(90, 0, 1, 0);
        for (auto& spoke : spokes)
        {
            spoke.draw();
        }
    }

    Torus tire;
    Cylinder axle;
    float radius, thickness;
    const static int num_spokes = 18; //36
    std::array<Cylinder, num_spokes> spokes;
    Wheel(float radius_ = 3.3, float thickness_ = 0.18): GenericObject()
    {
        radius = radius_;
        thickness = thickness_;

        tire.slices = 20;
        tire.rings = 50;
        tire.color = {0.1, 0.1, 0.1, 1};

        axle.color = {0.5, 0.5, 0.5, 1};

        Pose pose;
        pose.R = {1, 0, 0, 0};
        float delta = 180./num_spokes;
        for (auto& spoke : spokes)
        {
            spoke.setPose(pose);
            spoke.color = {0.3, 0.3, 0.3, 1};
            pose.R.w += delta;
        }

        color.x = color.y = color.z = 0.9;
        color.w = 1.0;
    }
};  // class Wheel

#endif  // _WHEEL_HPP_
