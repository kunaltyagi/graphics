#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

// not working

#include <generic_object.hpp>
#include <triangle.hpp>

struct Square: public GenericObject
{
    void setupObject(void)
    {
        for (auto& triangle : triangles)
        {
            triangle.setupObject();
        }
        _drawList = glGenLists(1);
        glNewList(_drawList, GL_COMPILE);
        glShadeModel(GL_SMOOTH);
        glBegin(GL_TRIANGLES);
        drawSquare();
        glEnd();
        glEndList();
    }

    void setupMaterial(void)
    {
        for (auto& triangle : triangles)
        {
            triangle.setupMaterial();
        }
    }

    void drawSquare(void)
    {
            glPushMatrix();
        for (auto& triangle : triangles)
        {
            triangle.transformObj();
            std::cout << triangle.getPose().R << '\n';
            triangle.drawTriangle();
        }
        glEnd();
            glPopMatrix();
        /* for (auto& triangle : triangles) */
        /* { */
        /*     triangle.draw(); */
        /* } */
    }

    void draw(void)
    {
        std::cout << "Square  :\t";
        GenericObject::draw();
        /* for (auto& triangle : triangles) */
        /* { */
        /*     triangle.draw(); */
        /* } */
    }

    static const int num_triangles = 2;
    std::array<Triangle, num_triangles> triangles;
    Square(float len = 1, float width = 1):
        GenericObject(Vector(len, width, 1))
    {
        Point vertices[Triangle::num_vertex] =
                {{0, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 0, 1}};
        for (auto& triangle : triangles)
        {
            triangle.setVertices(vertices);
        }
        Pose far;
        far.R.setPoint(0, 0, 1, 180);
        far.T.setPoint(-1, -1, 0, 1);
        triangles[1].setPose(far);

        color.x = color.y = color.z = 0.8;
        color.w = 1.0;
    }
};  // class Square

#endif  // _SQUARE_HPP_
