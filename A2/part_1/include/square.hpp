#ifndef _SQUARE_HPP_
#define _SQUARE_HPP_

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
        GenericObject::setupObject();
    }

    void setupMaterial(void)
    {
        for (auto& triangle : triangles)
        {
            triangle.setupMaterial();
        }
    }

    void drawObject(void)
    {
        for (auto& triangle : triangles)
        {
            triangle.draw();
        }
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

        this->_origin.x = 0.5;
        this->_origin.y = 0.5;

        color.x = color.y = color.z = 1;
        color.w = 1.0;
    }
};  // class Square

#endif  // _SQUARE_HPP_
