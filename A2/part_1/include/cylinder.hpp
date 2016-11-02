#ifndef _CYLINDER_HPP_
#define _CYLINDER_HPP_

#include <generic_object.hpp>

struct Cylinder: public GenericObject
{
    float base_radius = 0.5, top_radius = 0.5, height = 1.0;
    int slices = 15, stacks = 1;

    void setupObject(void)
    {
        _drawList = glGenLists(1);
        qobj = gluNewQuadric();

        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glNewList(_drawList, GL_COMPILE);
        drawObject();
        glEndList();
    }

    void drawObject(void)
    {
        gluCylinder(qobj, base_radius, top_radius, height, slices, stacks);
    }

    void _cleanup()
    {
        gluDeleteQuadric(qobj);
    }

    Cylinder(float r_base = 0.5, float r_top = 0.5, float h = 1,
             int slice = 15, int stack = 1):
        GenericObject(), base_radius(r_base), top_radius(r_top), height(h),
        slices(slice), stacks(stack)
    {
        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Cylinder

#endif  // _CYLINDER_HPP_
