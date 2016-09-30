#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <generic_object.hpp>

struct Cube: public GenericObject
{
    void setupObject(void)
    {
        _drawList = glGenLists(1);
        glNewList(_drawList, GL_COMPILE);

        float a = 0.5;
        float vertices[] = {
             a,  a, -a,
            -a,  a, -a,
            -a, -a, -a,
             a,  a,  a,
            -a,  a,  a,
            -a, -a,  a,

             a,  a, -a,
             a, -a, -a,
            -a, -a, -a,
             a,  a,  a,
             a, -a,  a,
            -a, -a,  a,

             a,  a,  a,
             a, -a,  a,
             a, -a, -a,
            -a,  a,  a,
            -a, -a,  a,
            -a, -a, -a,

             a,  a,  a,
             a,  a, -a,
             a, -a, -a,
            -a,  a,  a,
            -a,  a, -a,
            -a, -a, -a,

             a,  a,  a,
            -a,  a,  a,
            -a,  a, -a,
             a, -a,  a,
            -a, -a,  a,
            -a, -a, -a,

             a,  a,  a,
             a,  a, -a,
            -a,  a, -a,
             a, -a,  a,
             a, -a, -a,
            -a, -a, -a
        };

        glShadeModel(GL_SMOOTH);
        /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < 12; ++i)
        {
            std::cout << i << ": ";
            std::cout << vertices[9*i + 0] << '\t';
            glVertex3fv(vertices + 9*i + 0);
            std::cout << vertices[9*i + 3] << '\t';
            glVertex3fv(vertices + 9*i + 3);
            std::cout << vertices[9*i + 6] << '\n';
            glVertex3fv(vertices + 9*i + 6);
        }
        glEnd();
        /* glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); */
        glEndList();
    }

    float side = 1;
    Cube(): GenericObject() {}
    Cube(float a):
        GenericObject(Vector(a, a, a))
    {
        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Cube

#endif  // _CUBE_HPP_
