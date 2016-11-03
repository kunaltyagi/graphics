#ifndef _WHEEL_HPP_
#define _WHEEL_HPP_

#include <generic_object.hpp>
#include <cylinder.hpp>
#include <torus.hpp>

struct Wheel: public GenericObject
{
    void setupObject(void)
    {
        tire.setupObject();
        axle.setupObject();
        spokes[0].setupObject();
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
        spokes[0].setupMaterial();
    }

    void drawObject()
    {
        /* tire.draw(); */
        /* axle.draw(); */
        spokes[0].draw();
    }

    Torus tire;
    Cylinder axle;
    const static int num_spokes = 1; //36
    std::array<Cylinder, num_spokes> spokes;
    Wheel(): GenericObject()
    {
        tire.rInner = 0.18;
        tire.rOuter = 3.3;
        tire.slices = 20;
        tire.rings = 50;
        axle.base_radius = axle.top_radius = tire.rInner;
        axle.height = 3 * tire.rInner;

        for (auto& spoke : spokes)
        {
            spoke.height = 5;
            spoke.base_radius = spoke.top_radius = 0.05;
        }


        color.x = color.y = color.z = 0.9;
        color.w = 1.0;
    }
};  // class Wheel

#endif  // _WHEEL_HPP_
