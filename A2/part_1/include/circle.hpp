#ifndef _CIRCLE_HPP_
#define _CIRCLE_HPP_

#include <generic_object.hpp>
#include <triangle.hpp>

struct Circle: public GenericObject
{
    float radius;
    int slices;
    Triangle sector;
    Circle(float radius_ = 1, int slices_ = 25): GenericObject()
    {
        radius = radius_;
        slices = slices_;
    }

    void setupObject(void)
    {
        float delta = deg2rad(360)/slices;
        sector.setVertices({Point(0, 0, 0, 1), Point(radius, 0, 0, 1),
                Point(radius * std::cos(delta), radius * std::sin(delta), 0, 1)});

        sector.setupObject();
        GenericObject::setupObject();
    }

    void setupMaterial(void)
    {
        sector.setupMaterial();
    }

    void drawObject(void)
    {
        float delta = 360./slices;
        for (int i = 0; i < slices; ++i)
        {
            sector.drawObject();
            glRotatef(delta, 0, 0, 1);
        }
    }
};

#endif  // _CIRCLE_HPP_
