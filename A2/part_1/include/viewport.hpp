#ifndef _VIEWPORT_HPP_
#define _VIEWPORT_HPP_

#include <glut/glut_framework.hpp>
#include <object.hpp>

struct Viewport: public glut_framework::GlutFramework
{
    using GF = glut_framework::GlutFramework;

    Viewport(): GF()
    {
        this->setTitle("Assignment 2 (I)");
    }

    void setBaseObj(ObjectPtr obj_) { _baseObject = obj_; }

    void display(float dTime)
    {
        _baseObject->draw();
        std::cout << dTime << '\n';
    }
protected:
    Point _bg;  // background color
    ObjectPtr _baseObject;
};  // class Viewport

#endif  // _VIEWPORT_HPP_
