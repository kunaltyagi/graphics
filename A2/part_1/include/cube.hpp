#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <generic_object.hpp>
#include <square.hpp>

struct Cube: public GenericObject
{
    void setupObject(void)
    {
        for (auto& square : squares)
        {
            square.setupObject();
        }
        _drawList = glGenLists(1);
        glNewList(_drawList, GL_COMPILE);
        glShadeModel(GL_SMOOTH);
        this->drawObject();
        glEndList();
    }

    void setupMaterial(void)
    {
        for (auto& square : squares)
        {
            square.setupMaterial();
        }
    }

    void drawObject(void)
    {
        for (auto& square : squares)
        {
            square.draw();
        }
    }

    static const int num_squares = 6;
    std::array<Square, num_squares> squares;

    Cube(float a = 1): GenericObject(Vector(a, a, a))
    {
        int offset = 0;
        Pose far;
        far.T.setPoint(0, 0, 0.5, 1);

        squares[offset + 0].setPose(far);
        far.R.setPoint(0, 1, 0, 180);
        squares[offset + 1].setPose(far);
        offset += 2;

        far.R.setPoint(1, 0, 0, 90);
        squares[offset + 0].setPose(far);
        far.R.setPoint(1, 0, 0, -90);
        squares[offset + 1].setPose(far);
        offset += 2;

        far.R.setPoint(0, 1, 0, 90);
        squares[offset + 0].setPose(far);
        far.R.setPoint(0, 1, 0, -90);
        squares[offset + 1].setPose(far);

        color.x = color.y = color.z = 1;
        color.w = 1.0;
    }
};  // class Cube

#endif  // _CUBE_HPP_
