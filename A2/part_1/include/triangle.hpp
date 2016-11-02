#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <generic_object.hpp>

struct Triangle: public GenericObject
{
    void setupObject(void)
    {
        _drawList = glGenLists(1);
        glNewList(_drawList, GL_COMPILE);
        glShadeModel(GL_SMOOTH);
        this->drawObject();
        glEndList();
    }

    void drawObject(void)
    {
        glBegin(GL_TRIANGLES);
        for (auto& vertex : vertices)
        {
            glVertex4f(vertex.x, vertex.y, vertex.z, vertex.w);
        }
        glEnd();
    }

    const static int num_vertex = 3;
    std::array<Point, num_vertex> vertices;

    void setVertices(const Point (&vertex)[num_vertex])
    {
        std::copy(std::begin(vertex), std::end(vertex), vertices.begin());
    }

    Triangle(){}
    Triangle(const Point (&vertex)[num_vertex])
    {
        setVertices(std::forward<const Point[num_vertex]>(vertex));
        color.x = color.y = color.z = 1;
        color.w = 1.0;
    }
};  // class Triangle

#endif  // _TRIANGLE_HPP_
