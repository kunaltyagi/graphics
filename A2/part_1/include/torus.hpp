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
        /* int numc = 8, numt = 25; */
        /* int i, j, k; */
        /* double s, t, x, y, z, twopi; */

        /* twopi = 2 * (double)M_PI; */
        /* for (i = 0; i < numc; i++) */
        /* { */
        /*    glBegin(GL_QUAD_STRIP); */
        /*    for (j = 0; j <= numt; j++) */
        /*    { */
        /*       for (k = 1; k >= 0; k--) */
        /*       { */
        /*          s = (i + k) % numc + 0.5; */
        /*          t = j % numt; */

        /*          x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt); */
        /*          y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt); */
        /*          z = .1 * sin(s * twopi / numc); */
        /*          glVertex3f(x, y, z); */
        /*       } */
        /*    } */
        /*   glEnd(); */
        /* } */
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
