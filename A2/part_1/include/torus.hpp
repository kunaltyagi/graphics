#ifndef _TORUS_HPP_
#define _TORUS_HPP_

#include <generic_object.hpp>

struct Torus: public GenericObject
{
    void setupObject(void)
    {
        _drawList = glGenLists(1);
        glNewList(_drawList, GL_COMPILE);
        glutSolidTorus(rInner, rOuter, slices, rings);
        glEndList();
    }

    float rInner = 0.8, rOuter = 1.2;
    int slices = 10, rings = 25;

    Torus(): GenericObject() {}
    Torus(float r_inner, float r_outer, int slice, int ring):
        GenericObject(), rInner(r_inner), rOuter(r_outer),
        slices(slice), rings(ring)
    {
        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Torus

#endif  // _TORUS_HPP_
