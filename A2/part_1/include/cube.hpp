#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <generic_object.hpp>

struct Cube: public GenericObject
{
    void setupObject(void)
    {
        _drawList = glGenLists(1);

        float vertices[] = {
                -1.0f,-1.0f,-1.0f, // triangle 1 : begin
                -1.0f,-1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, // triangle 1 : end
                 1.0f, 1.0f,-1.0f, // triangle 2 : begin
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f,-1.0f, // triangle 2 : end
                 1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f,-1.0f,
                 1.0f,-1.0f,-1.0f,
                 1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f, 1.0f,
                -1.0f,-1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f,-1.0f, 1.0f,
                 1.0f,-1.0f, 1.0f,
                 1.0f, 1.0f, 1.0f,
                 1.0f,-1.0f,-1.0f,
                 1.0f, 1.0f,-1.0f,
                 1.0f,-1.0f,-1.0f,
                 1.0f, 1.0f, 1.0f,
                 1.0f,-1.0f, 1.0f,
                 1.0f, 1.0f, 1.0f,
                 1.0f, 1.0f,-1.0f,
                -1.0f, 1.0f,-1.0f,
                 1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f,-1.0f,
                -1.0f, 1.0f, 1.0f,
                 1.0f, 1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,
                 1.0f,-1.0f, 1.0f};
        /* glBegin(GL_TRIANGLES); */
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisableClientState(GL_VERTEX_ARRAY);
        /* glEnd(); */
        glEndList();

        glShadeModel(GL_SMOOTH);
    }

    float side = 10;
    int slices = 1, stacks = 1;
    Cube(): GenericObject() {}
    Cube(float a, int slice, int stack):
        GenericObject(), side(a),
        slices(slice), stacks(stack)
    {
        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Cube

#endif  // _CUBE_HPP_
