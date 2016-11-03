#ifndef _TORUS_HPP_
#define _TORUS_HPP_

#include <generic_object.hpp>

struct Torus: public GenericObject
{
    void setupObject(void)
    {
        _drawList = glGenLists(1);
        glNewList(_drawList, GL_COMPILE);
        glPushMatrix();
        drawObject();
        glPopMatrix();
        glEndList();
    }

    void drawObject(void)
    {
        glutSolidTorus(rInner, rOuter, slices, rings);
        /* glutWireTorus(rInner, rOuter, slices, rings); */
    }

    float rInner, rOuter;
    int slices, rings;

    Torus(float r_inner = 0.8, float r_outer = 1.2, int slice = 10,
          int ring = 25): GenericObject(), rInner(r_inner), rOuter(r_outer),
                          slices(slice), rings(ring)
    {
        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Torus

#endif  // _TORUS_HPP_
