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
        glPushMatrix();
        drawObject();
        glPopMatrix();
        glEndList();
    }
    void drawObject()
    {
        gluSphere(qobj, radius, slices, stacks);
    }
    void _cleanup()
    {
        gluDeleteQuadric(qobj);
    }

    float radius;
    int slices, stacks;
    Sphere(float r = 1, int slice = 15, int stack = 15):
        GenericObject(), radius(r),
        slices(slice), stacks(stack)
    {
        color.x = color.y = color.z = 0.7;
        color.w = 1.0;
    }
};  // class Sphere

#endif  // _SPHERE_HPP_
