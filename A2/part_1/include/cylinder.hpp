#ifndef _CYLINDER_HPP_
#define _CYLINDER_HPP_

#include <generic_object.hpp>

void errorCallback()
{
   exit(0);
}

struct Cylinder: public GenericObject
{
    void load(void)
    {
        std::cout << color << '\n';
        _drawList = glGenLists(1);
        qobj = gluNewQuadric();
        gluQuadricCallback(qobj, GLU_ERROR, errorCallback);

        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
        gluQuadricNormals(qobj, GLU_SMOOTH);
        glNewList(_drawList, GL_COMPILE);
        gluCylinder(qobj, base_radius, top_radius, height, slices, stacks);
        glEndList();
    }
    void _cleanup()
    {
        gluDeleteQuadric(qobj);
    }

    float base_radius = 0.5, top_radius = 0.5, height = 1.0;
    int slices = 15, stacks = 1;
    Cylinder(): GenericObject() {}
    Cylinder(float r_base, float r_top, float h, int slice, int stack = 1):
        GenericObject(), base_radius(r_base), top_radius(r_top), height(h),
        slices(slice), stacks(stack)
    {
        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Cylinder

#endif  // _CYLINDER_HPP_