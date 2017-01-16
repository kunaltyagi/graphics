#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <generic_object.hpp>

struct Cube: public GenericObject
{
    void setupObject(void);

    Cube(): GenericObject() {}

    Cube(float a):
        GenericObject(Vector(a, a, a))
    {
        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Cube

#endif  // _CUBE_HPP_
