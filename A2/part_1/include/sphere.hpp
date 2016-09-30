#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include <generic_object.hpp>

struct Sphere: public GenericObject
{
    void setupObject(void)
    {
        _drawList = glGenLists(1);
        qobj = gluNewQuadric();

        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glNewList(_drawList, GL_COMPILE);
        gluSphere(qobj, radius, slices, stacks);
        glEndList();
    }
    void _cleanup()
    {
        gluDeleteQuadric(qobj);
    }

    float radius = 1;
    int slices = 15, stacks = 15;
    Sphere(): GenericObject() {}
    Sphere(float r, int slice, int stack):
        GenericObject(), radius(r),
        slices(slice), stacks(stack)
    {
        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Sphere

#endif  // _SPHERE_HPP_
